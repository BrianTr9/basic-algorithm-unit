#include <bits/stdc++.h>
#define ll long long
using namespace std;

int n,m,timer,low[10000],num[10000];
vector <int> adj[10000];
vector <pair<int,int>> bridges;
void input()
{
    cin>>n>>m;
    for (int i=1;i<=m;i++)
    {
        int x,y;
        cin >>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
}
void dfs(int i,int p)
{
    low[i]=num[i]=++timer;
    for (auto u :adj[i])
    {
       if(u!=p)
        {
            if(num[u]==-1)
            {
                dfs(u,i);
                low[i]=min(low[i],low[u]);
            } else low[i]=min(low[i],num[u]);
        }
        if (num[i]<low[u]) bridges.push_back(make_pair(i,u));
    }
}
int main()
{
    input();
    timer=0;
    memset(num,-1,sizeof(num));
    cout<<"-------------------------"<<endl;
    dfs(1,0);
    for (auto i:bridges) cout<<i.first<<" "<<i.second<<endl;
    cout<<"-------------------------"<<endl;
    return 0;
}
