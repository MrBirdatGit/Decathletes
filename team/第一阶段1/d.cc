#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
char str[30];
ll dp[30][30];

int main()
{
	while(~scanf("%s", str+1)){
		memset(dp, 0, sizeof(dp));
		int n=strlen(str+1);
		dp[0][0]=1;
		for(int i=1;i<=n;i++){
			for(int j=0;j<=i;j++){
				if(str[i]=='+'){
					if(j==0)continue;
					dp[i][j]=(dp[i-1][j-1]+dp[i-1][j]*j);
				}
				else {
					dp[i][j]=(dp[i-1][j]*j+dp[i-1][j+1]*(j+1)*(j+1));
				}
			}
		}
		printf("%lld\n", dp[n][0]);
	}
}

