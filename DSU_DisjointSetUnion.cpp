/**
 * Disjoint Set Union (Union-Find) Data Structure
 * 
 * Description:
 * DSU maintains a collection of disjoint (non-overlapping) sets.
 * Each set has a representative element (root).
 * 
 * Operations:
 * - find(x): Find the root of set containing x
 * - unite(x, y): Merge sets containing x and y
 * - sameSet(x, y): Check if x and y are in the same set
 * 
 * Optimizations:
 * - Path Compression: Make tree flat during find()
 * - Union by Rank/Size: Attach smaller tree under larger tree
 * 
 * Time Complexity: O(α(n)) ≈ O(1) per operation
 * where α(n) is the inverse Ackermann function (< 5 for n < 10^600)
 * 
 * Space Complexity: O(n)
 * 
 * Applications:
 * - Kruskal's MST algorithm
 * - Connected components in graph
 * - Cycle detection
 * - Dynamic connectivity
 * - LCA (Lowest Common Ancestor) offline
 * 
 * Author: Truong Trung Bao
 * Source: Basic Algorithm Unit - HUST
 */

#include <bits/stdc++.h>
using namespace std;

//===============================TrB===============================//

#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)

const int MAX = 100005;

int parent[MAX];    // parent[i] = parent of node i
int setRank[MAX];   // setRank[i] = rank of tree rooted at i
int setSize[MAX];   // setSize[i] = size of set containing i
int n;              // Number of elements

// Initialize DSU: each element is its own set
void init(int n) {
    FOR(i, 1, n) {
        parent[i] = i;
        setRank[i] = 0;
        setSize[i] = 1;
    }
}

// Find root with path compression
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);  // Path compression
    }
    return parent[x];
}

// Union by rank: attach shorter tree under taller tree
void uniteByRank(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    
    if (rootX == rootY) return;  // Already in same set
    
    // Union by rank
    if (setRank[rootX] < setRank[rootY]) {
        parent[rootX] = rootY;
    } else if (setRank[rootX] > setRank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        setRank[rootX]++;
    }
}

// Union by size: attach smaller tree under larger tree
void uniteBySize(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    
    if (rootX == rootY) return;  // Already in same set
    
    // Union by size
    if (setSize[rootX] < setSize[rootY]) {
        parent[rootX] = rootY;
        setSize[rootY] += setSize[rootX];
    } else {
        parent[rootY] = rootX;
        setSize[rootX] += setSize[rootY];
    }
}

// Check if x and y are in the same set
bool sameSet(int x, int y) {
    return find(x) == find(y);
}

// Get size of set containing x
int getSetSize(int x) {
    return setSize[find(x)];
}

// Count number of disjoint sets
int countSets(int n) {
    int count = 0;
    FOR(i, 1, n) {
        if (find(i) == i) count++;
    }
    return count;
}

// Example usage
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cout << "DSU Demo - Managing Disjoint Sets" << endl;
    cout << "==================================\n" << endl;
    
    n = 10;
    init(n);
    
    cout << "Initial: " << n << " elements, each in its own set" << endl;
    cout << "Number of sets: " << countSets(n) << "\n" << endl;
    
    // Unite some sets
    cout << "Performing unions:" << endl;
    uniteBySize(1, 2);
    cout << "unite(1, 2)" << endl;
    
    uniteBySize(3, 4);
    cout << "unite(3, 4)" << endl;
    
    uniteBySize(1, 3);
    cout << "unite(1, 3) - merges {1,2} and {3,4}" << endl;
    
    uniteBySize(5, 6);
    cout << "unite(5, 6)" << endl;
    
    cout << "\nNumber of sets: " << countSets(n) << "\n" << endl;
    
    // Check connectivity
    cout << "Checking connectivity:" << endl;
    cout << "sameSet(1, 4)? " << (sameSet(1, 4) ? "YES" : "NO") << endl;
    cout << "sameSet(1, 5)? " << (sameSet(1, 5) ? "YES" : "NO") << endl;
    cout << "sameSet(2, 3)? " << (sameSet(2, 3) ? "YES" : "NO") << "\n" << endl;
    
    // Get set sizes
    cout << "Set sizes:" << endl;
    cout << "Set containing 1: " << getSetSize(1) << " elements" << endl;
    cout << "Set containing 5: " << getSetSize(5) << " elements" << endl;
    cout << "Set containing 7: " << getSetSize(7) << " elements" << endl;
    
    return 0;
}
