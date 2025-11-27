#include <bits/stdc++.h>
using namespace std;
int n,cnt=0; // Number of nodes
vector<int> adj[100009]; // Adjacency list
bool isCut[100009]; // Articulation points
vector<bool> visited;
vector<int> tin, low;
int timer;
void markCutPoint(int v)
{
    isCut[v]=1;
}
void dfs(int v, int p) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children=0;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p!=-1)
                markCutPoint(v);
            ++children;
        }
    }
    if(p == -1 && children > 1)
        markCutPoint(v);
}

void findCutPoints() {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs (i,-1);
    }
}
int main()
{
    //freopen("test.inp","r",stdin);
    int m;
    cin>>n>>m;
    memset(isCut,0,sizeof(isCut));
    for (int i=1;i<=m;++i)
    {
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    findCutPoints();
    for (int i=1;i<=n;++i) if (isCut[i]) cnt++;
    cout<<cnt;
    return 0;
}

