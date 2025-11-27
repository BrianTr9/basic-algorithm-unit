#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int maxx=1000;
int n,m;
tuple <int,int,int> e[maxx];
int p[maxx],sz[maxx];
void input()
{
    cin>>n>>m;
    for (int i=1;i<=m;i++) {
        int x,y,w;
        cin>>x>>y>>w;
        e[i]=make_tuple(w,x,y);
    }
}
int root(int u)
{
    if (p[u]==u) return u;
    return p[u]=root(p[u]);
}
void solve()
{
    sort(e+1,e+m+1);
    for (int i=1;i<=n;i++) {
            p[i]=i;
            sz[i]=1;
    }
    int cnt=0;
    int i=1;
    int res=0;
    while (i<=m) {
        int x=get<1>(e[i]);
        int y=get<2>(e[i]);
        int rootX=root(x);
        int rootY=root(y);
        if (rootX!=rootY) {
            res+=get<0>(e[i]);
            if (sz[rootX]<sz[rootY]) swap(rootX,rootY);
            p[rootY]=rootX;
            sz[rootX]+=sz[rootY];
            cnt++;
        }
        i++;
        if (cnt==n-1) break;
    }
    if (cnt==n-1) cout<<res<<endl; else cout<<"-1"<<endl;
}
int main()
{
    input();
    solve();
    return 0;
}
