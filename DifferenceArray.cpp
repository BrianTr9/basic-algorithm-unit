#include <bits/stdc++.h>
using namespace std;
#define ll long long;

const int maxx=1e3+1;
int n,q;
int a[maxx],d[maxx];
void update(int l, int r, int val)
{
    d[l-1]+=val;
    d[r]-=val;
}
void input()
{
    cin>>n>>q;
    for (int i=0;i<n;i++) {
        cin>>a[i];
        if (i==0) d[i]=a[i]; else d[i]=a[i]-a[i-1];
    }
    for (int i=1;i<=q;i++) {
        int l,r,val;
        cin>>l>>r>>val;
        update(l,r,val);
    }
}
void output()
{
    int cur=0;
    for (int i=0;i<n;i++) {
        cur+=d[i];
        cout<<cur<<" ";
    }
}
int main()
{
    input();
    output();
    return 0;
}
