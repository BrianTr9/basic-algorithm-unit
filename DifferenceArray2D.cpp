#include <bits/stdc++.h>
using namespace std;

const int maxx=1e3;
int a[maxx][maxx], f[maxx][maxx];
int n,m,q;
void input()
{
    cin>>n>>m;
    int maxSize=max(n,m);
    for (int i=0;i<=maxSize;i++) {
        f[0][i]=0;
        f[i][0]=0;
    }
    for (int i=1;i<=n;i++) 
        for (int j=1;j<=m;j++) cin>>a[i][j];
}
void solve()
{
    cin>>q;
    while (q--) {
        int x1,y1,x2,y2,val;
        cin>>x1>>y1>>x2>>y2>>val;
        f[x1][y1]+=val;
        f[x2+1][y1]-=val;
        f[x1][y2+1]-=val;
        f[x2+1][y2+1]+=val;
        
    }
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++) {
            f[i][j]=f[i][j]+f[i-1][j]+f[i][j-1]-f[i-1][j-1];
        }
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++) f[i][j]+=a[i][j];
        
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++) cout<<f[i][j]<<" ";
        cout<<endl;
    }
}
int main()
{
    freopen("test.INP","r",stdin);
    freopen("test.OUT","w",stdout);
    input();
    solve();
    return 0;
}