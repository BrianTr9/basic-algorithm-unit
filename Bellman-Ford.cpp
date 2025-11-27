#include <iostream>
#include <vector>
#include <limits.h>
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, weight;
};

void bellmanFord(int vertices, int edges, vector<Edge>& graph, int source) {
    vector<int> distance(vertices, INT_MAX);
    vector<int> parent(vertices, -1);
    distance[source] = 0;

    for (int i = 1; i <= vertices - 1; ++i) {
        for (int j = 0; j < edges; ++j) {
            int u = graph[j].u;
            int v = graph[j].v;
            int weight = graph[j].weight;
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
            }
        }
    }

    // Check for negative cycle
    for (int j = 0; j < edges; ++j) {
        int u = graph[j].u;
        int v = graph[j].v;
        int weight = graph[j].weight;
        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            cout << "Graph contains a negative-weight cycle" << endl;
            return;
        }
    }

    // Print shortest distances
    cout << "Vertex Distance from Source" << endl;
    for (int i = 0; i < vertices; ++i) {
        if (distance[i] == INT_MAX) {
            cout << i << "\t\t" << "INF" << "\t\tNo Path" << endl;
        } else {
            cout << i << "\t\t" << distance[i] << "\t\t";

            // Trace path
            vector<int> path;
            for (int current = i; current != -1; current = parent[current]) {
                path.push_back(current);
            }
            reverse(path.begin(), path.end());

            cout << "Path: ";
            for (size_t k = 0; k < path.size(); ++k) {
                cout << path[k];
                if (k != path.size() - 1) {
                    cout << " <- ";
                }
            }
            cout << endl;
        }
    }
}

int main() {
    int vertices, edges, source;
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    cout << "Enter the number of edges: ";
    cin >> edges;

    vector<Edge> graph(edges);
    cout << "Enter edges (u v weight):" << endl;
    for (int i = 0; i < edges; ++i) {
        cin >> graph[i].u >> graph[i].v >> graph[i].weight;
    }

    cout << "Enter the source vertex: ";
    cin >> source;

    bellmanFord(vertices, edges, graph, source);

    return 0;
}
