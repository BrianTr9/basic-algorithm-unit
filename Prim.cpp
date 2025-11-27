#include <bits/stdc++.h>
#define ll long long
using namespace std;

int n,m;
vector<pair<int,int>> adj[100011];
bool visited[100011];
void input()
{
    cin>>n>>m;
    for (int i=1;i<=m;i++)
    {
        int x,y,w;
        cin>>x>>y>>w;
        adj[x].push_back(make_pair(w,y));
        adj[y].push_back(make_pair(w,x));
    }
}
void solve()
{
    memset(visited,1,sizeof(visited));
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
    for(pair<int,int> i:adj[1]) q.push(i);
    visited[1]=0;
    ll res=0,cnt=0;
    while(!q.empty())
    {
        pair<int,int> v=q.top();
        q.pop();
        while(visited[v.second]==0)
        {
            v=q.top();
            q.pop();
        }
        cnt++;
        res+=v.first;
        int u=v.second;
        visited[u]=0;
        if (cnt==n-1) break;
        for(pair<int,int> i:adj[u])
            if(visited[i.second]==1) q.push(i);
    }
    cout<<res;
}
int main()
{
    input();
    solve();
    return 0;
}

