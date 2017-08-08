#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=1LL<<60;
int n,m;
int a[105000];
int b[105000];
int k[1050];
int p[1050];
ll dp[11][2050];
int main(){
	while(~scanf("%d%d",&n,&m)){
		for(int i=1;i<=n;i++)scanf("%d%d",&a[i],&b[i]);
		for(int i=1;i<=m;i++)scanf("%d%d",&k[i],&p[i]);
		for(int i=0;i<=10;i++){
			for(int j=0;j<=2000;j++){
				dp[i][j]=INF;
			}
			dp[i][0]=0;
			for(int j=1;j<=2000;j++){
				for(int w=1;w<=m;w++){
					if(p[w]<=i)continue;
					if(p[w]-i>j)continue;
					dp[i][j]=min(dp[i][j],dp[i][j-(p[w]-i)]+k[w]);
				}
			}
			for(int j=1999;j>=0;j--)dp[i][j]=min(dp[i][j],dp[i][j+1]);
		}
		bool ok=true;
		ll ans=0;
		for(int i=1;i<=n;i++){
			if(dp[b[i]][a[i]]>=INF){
				ok=false;
				break;
			}
			ans+=dp[b[i]][a[i]];
		}
		if(!ok)printf("-1\n");
		else printf("%lld\n",ans);
	}
}
