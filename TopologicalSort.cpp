#include <bits/stdc++.h>
using namespace std;

// Topological sort using Kahn's algorithm.
// Input: n m
// m lines: u v  (edge u -> v)
// Output: one topological order (space-separated) or IMPOSSIBLE if graph has a cycle.

// Core: Kahn's algorithm returning empty vector on cycle
vector<int> kahn_topo(int n, const vector<vector<int>> &graph){
    vector<int> indeg(n + 1, 0);
    for (int u = 1; u <= n; ++u) for (int v : graph[u]) ++indeg[v];
    queue<int> q;
    for (int i = 1; i <= n; ++i) if (indeg[i] == 0) q.push(i);
    vector<int> order; order.reserve(n);
    while (!q.empty()){
        int u = q.front(); q.pop(); order.push_back(u);
        for (int v : graph[u]) if (--indeg[v] == 0) q.push(v);
    }
    if ((int)order.size() != n) return {};
    return order;
}

// Read input into n and adjacency list. Returns false on EOF.
// Read a directed graph: n m followed by m edges (u v). Returns false on EOF.
bool read_input(istream &in, int &n, int &m, vector<vector<int>> &graph){
    if (!(in >> n >> m)) return false;
    graph.assign(n + 1, {});
    for (int i = 0; i < m; ++i){
        int u, v; in >> u >> v;
        graph[u].push_back(v);
    }
    return true;
}

// Write output from order; if empty -> IMPOSSIBLE
// Print the topological order or IMPOSSIBLE when cycle detected.
void write_output(ostream &out, const vector<int> &order){
    if (order.empty()){ out << "IMPOSSIBLE\n"; return; }
    for (size_t i = 0; i < order.size(); ++i){ if (i) out << ' '; out << order[i]; }
    out << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    vector<vector<int>> graph;
    if (!read_input(cin, n, m, graph)) return 0;

    auto order = kahn_topo(n, graph);
    write_output(cout, order);
    return 0;
}

