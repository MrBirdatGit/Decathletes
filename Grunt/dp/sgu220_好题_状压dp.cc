//好题
//在n*n的棋盘上放k个象使得任何两个象不能互相攻击(在同一对角线上)
//首先考虑到状压dp,按x+y从小到大,x-y+n是否被用过为状态dp
//但是x-y+n有20, 存不下
//这时候注意到黑白格之间不会互相攻击
//所以把黑白格分开考虑，最后再合并一下
//这样状态就只有1<<10了
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dp[21][11][1<<10];
int n, k;
int main(){
	memset(dp, 0, sizeof(dp));
	scanf("%d%d", &n, &k);
	if(n==1)return 0*printf("1\n");
	dp[0][0][0]=1;
	dp[1][0][0]=1;
	for(int i=2;i<=2*n;i+=2){
		for(int j=0;j<10;j++){
			for(int st=0;st<1<<10;st++){
				if(dp[i-2][j][st]==0)continue;
				dp[i][j][st]+=dp[i-2][j][st];
				for(int x=max(1, i-n);x<=min(n, i-1);x++){
					int y=i-x;
					int id=0;
					if(x==y)id=0;
					else if(x>y)id=x-y;
					else id=y-x-1;
					if(st&(1<<id))continue;
					dp[i][j+1][st|(1<<id)]+=dp[i-2][j][st];
				}
			}
		}
	}
	for(int i=3;i<=2*n;i+=2){
		for(int j=0;j<10;j++){
			for(int st=0;st<1<<10;st++){
				if(dp[i-2][j][st]==0)continue;
				dp[i][j][st]+=dp[i-2][j][st];
				for(int x=max(1, i-n);x<=min(n, i-1);x++){
					int y=i-x;
					int id=0;
					if(x>y)id=x-y;
					else id=y-x-1;
					if(st&(1<<id))continue;
					dp[i][j+1][st|(1<<id)]+=dp[i-2][j][st];
				}
			}
		}
	}
	ll ans=0;
	for(int i=max(0, k-10);i<=min(k, 10);i++){
		int j=k-i;
		for(int is=0;is<1<<10;is++){
			for(int js=0;js<1<<10;js++){
				ans+=dp[2*n][i][is]*dp[2*n-1][j][js];
			}
		}
	}
	printf("%lld\n", ans);
}

