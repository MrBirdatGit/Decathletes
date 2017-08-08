#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,d,c;
ll dp[1050];
ll a[1050];
int main(){
	scanf("%lld%lld%lld",&n,&d,&c);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	dp[0]=0;
	for(int i=1;i<=n;i++){
		ll M=1LL<<61;
		ll sum=0;
		for(int j=i;j>=1;j--){
			sum+=a[j];
			M=min(M,(1LL*(i-j+1)*a[i]-sum)*c+dp[j-1]);
		}
		dp[i]=M+d;
	}
	printf("%lld\n",dp[n]);
}
