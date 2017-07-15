#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll k;
ll dp[105000];
ll x[105000];
int tot;
int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d%lld", &n, &k);
		tot=0;
		x[0]=-1;
		for(int i=1;i<=n;i++){
			ll tmp;
			scanf("%lld", &tmp);
			if(tmp!=x[tot])x[++tot]=tmp;
		}
		for(int i=0;i<=tot;i++)dp[i]=-1;
		dp[1]=0;
		for(int i=2;i<=tot;i++){
			for(int j=1;j<=30;j++){
				if(i-j<1)break;
				int dis=x[i]-x[i-j];
				if(dis>30)break;
				if(dp[i]==-1)dp[i]=dp[i-j]+(1LL<<dis)+k;
				else dp[i]=min(dp[i], dp[i-j]+(1LL<<dis)+k);
			}
		}
		printf("%lld\n", dp[tot]);
	}
}

