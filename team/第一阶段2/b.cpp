#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
long long dp[2][4000],n;
struct dian
{
    long long x,c;
}d[4000];

bool cmp(dian a, dian b)
{
    return a.x<b.x;
}

int main()
{
    long long minc;
    while(scanf("%lld",&n)!=EOF)
    {
        for(int i=1; i<=n; i++) scanf("%d %d",&d[i].x,&d[i].c);
        sort(d+1,d+n+1,cmp);
        memset(dp,0,sizeof(dp));
        minc=0;
        for(int i=1; i<=n; i++)
        {
            dp[i%2][i]=minc+d[i].c;
            minc=dp[i%2][i];
            for(int j=i-1; j>0; j--)
            {
                dp[i%2][j]=dp[(i-1)%2][j]+d[i].x-d[j].x;
                if(dp[i%2][j]<minc) minc=dp[i%2][j];
            }
        }
        printf("%lld\n",minc);
    }
    return 0;
}