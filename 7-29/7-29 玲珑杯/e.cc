#include <bits/stdc++.h>
using namespace std;
int a[1050];
char c[1050];
double p[1050];
char s[3];
double dp[1050][20][2];
int n;
int main(){
	scanf("%d",&n);
	for(int i=0;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		c[i]=s[0];
	}
	for(int i=1;i<=n;i++)scanf("%lf",&p[i]);
	
	memset(dp,0,sizeof(dp));
	
	for(int i=0;i<20;i++){
		if((a[0]>>i)&1){
			dp[0][i][1]=1;
		}
		else dp[0][i][0]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<20;j++){
			for(int k=0;k<2;k++){
				int f=(a[i]>>j)&1;
				dp[i][j][k]+=dp[i-1][j][k]*p[i];
				int to=k;
				if(c[i]=='^')to^=f;
				else if(c[i]=='|')to|=f;
				else to&=f;
				dp[i][j][to]+=dp[i-1][j][k]*(1-p[i]);
			}
		}
	}
	
	double ans=0;
	
	for(int i=0;i<20;i++){
		ans+=1.0*dp[n][i][1]*(1<<i);
		//printf("%.6f\n",ans);
		//return 0;
	}
	
	printf("%.6f\n",ans);
}
