#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    int n;

    void buildTree(vector<int>& arr, int start, int end, int node) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            buildTree(arr, start, mid, 2 * node + 1);
            buildTree(arr, mid + 1, end, 2 * node + 2);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    int queryRange(int start, int end, int l, int r, int node) {
        if (r < start || l > end) return 0;
        if (l <= start && r >= end) return tree[node];
        int mid = (start + end) / 2;
        int leftSum = queryRange(start, mid, l, r, 2 * node + 1);
        int rightSum = queryRange(mid + 1, end, l, r, 2 * node + 2);
        return leftSum + rightSum;
    }

    void updateValue(int start, int end, int idx, int value, int node) {
        if (start == end) {
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                updateValue(start, mid, idx, value, 2 * node + 1);
            } else {
                updateValue(mid + 1, end, idx, value, 2 * node + 2);
            }
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        buildTree(arr, 0, n - 1, 0);
    }

    int queryRange(int l, int r) {
        return queryRange(0, n - 1, l, r, 0);
    }

    void updateValue(int idx, int value) {
        updateValue(0, n - 1, idx, value, 0);
    }
};

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree segTree(arr);

    cout << "Sum of values in given range = " << segTree.queryRange(1, 3) << endl;

    segTree.updateValue(1, 10);

    cout << "Updated sum of values in given range = " << segTree.queryRange(1, 3) << endl;

    return 0;
}