#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
ll power(ll n,ll k){
	ll ans=1;
	ll base=n;
	while(k){
		if(k&1)ans=ans*base%mod;
		k>>=1;
		base=base*base%mod;
	}
	return ans;
}
int main(){
	ll n,k;
	int t=0;
	while(~scanf("%lld%lld",&n,&k)){
		t++;
		printf("Case #%d: %lld\n",t,power(n%mod,k));
	}
}
