#include <bits/stdc++.h>
using namespace std;

const int maxx=1000;
int n,a[maxx],q,f1[maxx],f2[maxx];
void input()
{
    cin>>n;
    for (int i=1;i<=n;i++) cin>>a[i];
    cin>>q;
}
void update1(int u, int v)
{
    int idx=u;
    while (idx<=n) {
        f1[idx]=max(f1[idx],v);
        idx+= idx & (-idx);
    }
    f1[n+1]=max(f1[n+1],v);
}
void update2(int u, int v)
{
    int idx=u;
    while (idx>=1) {
        f2[idx]=max(f2[idx],v);
        idx-= idx & (-idx);
    }
    f2[0]=max(f2[0],v);
}
int parent(int u, int code)
{
    if (code==2) return max(u-(u&(-u)),0);
    if (code==1) return min(u+(u&(-u)),n+1);
}
int query(int l, int r)
{
    int k;
    int res=LONG_MIN;
    k=l;
    while (parent(k,1)<=r) {
        res=max(res,f2[k]);
        k=parent(k,1);
    }
    k=r;
    while (parent(k,2)>=l) {
        res=max(res,f1[k]);
        k=parent(k,2);
    }
    res=max(res,a[k]);
    return res;
}
void solve()
{
    for (int i=1;i<=maxx;i++) {
        f1[i]=INT_MIN;
        f2[i]=INT_MIN;
    }
    for (int i=1;i<=maxx;i++) {
        update1(i,a[i]);
        update2(i,a[i]);
    }
    while (q--) {
        int l,r;
        cin>>l>>r;
        cout<<query(l,r)<<endl;
    }
}
int main()
{
    input();
    solve();
    return 0;
}

