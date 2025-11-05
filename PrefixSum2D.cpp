#include <iostream>
#include <cstring>
#define ll long long
using namespace std;
int main()
{
   ll n,m,i,j;
   cin >> n>>m;
   ll a[n+1][m+1],pre[n+1][m+1];
   memset (pre,0,sizeof(pre));
   for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
        {
            cin >> a[i][j];
            pre[i][j]=pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1]+a[i][j];
        }
   ll h1,c1,h2,c2;
   cin >>h1>>c1>>h2>>c2;
   ll t=pre[h2][c2]-pre[h1-1][c2]-pre[h2][c1-1]+pre[h1-1][c1-1];
   cout<<t<<"\n";
   return 0;
}
