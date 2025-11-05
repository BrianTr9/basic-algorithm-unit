#include <bits/stdc++.h>
#define ll long long
using namespace std;

int n,m,timer,low[10000],num[10000];
vector <int> adj[10000];
stack<int> st;
vector <pair<int,int>> bridges;
bool inStack[10000];
void input()
{
    cin>>n>>m;
    for (int i=1;i<=m;i++)
    {
        int x,y;
        cin >>x>>y;
        adj[x].push_back(y);
    }
}
void dfs(int i)
{
    st.push(i);
    inStack[i]=1;
    low[i]=num[i]=++timer;
    for (auto u :adj[i])
       if(num[u]==-1)
        {
            dfs(u);
            low[i]=min(low[i],low[u]);
        } else low[i]=min(low[i],num[u]);
    if (low[i]==num[i])
    {
        cout <<"TPLT: ";
        while (true)
        {
            int k=st.top();
            st.pop();
            inStack[k]=0;
            cout<<k<<" ";
            if (k==i) break;
        }
        cout<<endl;
    }
}
int main()
{
    input();
    timer=0;
    memset(num,-1,sizeof(num));
    memset(inStack,0,sizeof(inStack));
    cout<<"-------------------------"<<endl;
    for (int v=1;v<=n;v++) if (num[v]==-1) dfs(v);
    cout<<"-------------------------"<<endl;
    return 0;
}
