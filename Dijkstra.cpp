// Dijkstra's algorithm - shortest paths from single source
// Input (example):
// n m
// m lines: u v w   (1-indexed, directed)
// s
// Output: distances from s to 1..n (-1 for unreachable)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr long long INFLL = (long long)9e18;

// Core Dijkstra implementation (algorithm only, no IO)
vector<long long> dijkstra(int n, const vector<vector<pair<int,int>>> &graph, int src){
    vector<long long> dist(n+1, INFLL);
    dist[src] = 0;
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    pq.push({0, src});
    while(!pq.empty()){
        auto [d,u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        for (const auto &e : graph[u]){
            int v = e.first; int w = e.second;
            if (dist[v] > d + w){ dist[v] = d + w; pq.push({dist[v], v}); }
        }
    }
    return dist;
}

// Read input for dijkstra. Returns false on EOF.
bool read_input(istream &in, int &n, int &m, vector<vector<pair<int,int>>> &graph, int &src){
    if(!(in >> n >> m)) return false;
    graph.assign(n+1, {});
    for(int i = 0; i < m; ++i){
        int u, v, w; in >> u >> v >> w;
        graph[u].push_back({v, w});
        // if undirected: graph[v].push_back({u,w});
    }
    in >> src;
    return true;
}

void write_output(ostream &out, const vector<long long> &dist){
    for (size_t i = 1; i < dist.size(); ++i) {
        if (dist[i] >= INFLL) out << -1;
        else out << dist[i];
        if (i + 1 < dist.size()) out << ' ';
    }
    out << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s;
    vector<vector<pair<int,int>>> adj;
    if(!read_input(cin, n, m, adj, s)) return 0;
    auto dist = dijkstra(n, adj, s);
    write_output(cout, dist);
    return 0;
}
