#include <bits/stdc++.h>
using namespace std;
double dp[2550][55][55];
int T;
int n,m;
int main()
{
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        memset(dp,0,sizeof(dp));
        dp[0][n][m]=1;
        //cout<<"sb\n";
        for(int i=0;i<n*m;i++){
            for(int j=0;j<=n;j++){
                for(int k=0;k<=m;k++){
                    if(j*k!=0){
                        dp[i+1][j-1][k-1]+=dp[i][j][k]*(j*k)/(n*m-i);
                    }
                    if(j*(m-k)!=0){
                        dp[i+1][j-1][k]+=dp[i][j][k]*(j*(m-k))/(n*m-i);
                    }
                    if(k*(n-j)!=0){
                        dp[i+1][j][k-1]+=dp[i][j][k]*(k*(n-j))/(n*m-i);
                    }
                    if(n*m-i-j*k-j*(m-k)-k*(n-j)!=0){
                        dp[i+1][j][k]+=dp[i][j][k]*(n*m-i-j*k-j*(m-k)-k*(n-j))/(n*m-i);
                    }
                }
            }
        }
        double ans=0;
    for(int i=1;i<=n*m;i++){
        ans+=i*(dp[i][0][0]-dp[i-1][0][0]);
    }
    printf("%.10f\n",ans);
    }
    
}