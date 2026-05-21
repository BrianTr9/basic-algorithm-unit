#include <bits/stdc++.h>
using namespace std;

static const long long INF = (long long)4e18;

// Floyd-Warshall: all-pairs shortest paths
// Input (example):
// n m
// m lines: u v w   (1-indexed, directed)
// Output: n x n matrix, -1 for unreachable pairs
vector<vector<long long>> floydWarshall(int n, const vector<vector<long long>> &dist) {
    vector<vector<long long>> dp = dist;
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            if (dp[i][k] >= INF) continue;
            for (int j = 1; j <= n; ++j) {
                if (dp[k][j] >= INF) continue;
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }
    return dp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, INF));
    for (int i = 1; i <= n; ++i) dist[i][i] = 0;

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
        // If the graph is undirected, also set dist[v][u] = min(dist[v][u], w);
    }

    auto ans = floydWarshall(n, dist);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (ans[i][j] >= INF / 2) cout << -1;
            else cout << ans[i][j];
            if (j < n) cout << ' ';
        }
        cout << '\n';
    }

    return 0;
}