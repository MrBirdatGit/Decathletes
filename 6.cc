#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
ll power(ll n,ll p){
	ll ans=1;
	ll base=n;
	while(p){
		if(p&1){
			ans=ans*base%mod;		
		}
		p>>=1;
		base=base*base%mod;	
	}
	return ans;
}

ll n,m;

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld",&n,&m);
		if(n==1){printf("1\n");continue;}
		if(n%2==0){
			if(m==1){
				printf("1\n");
				continue;
			}
			ll f=2*(power(4,n/2)+mod-1)%mod;
			f=f*power(3,mod-2)%mod;
			ll p=(power(2,n)+mod-1)%mod;
			f=f*power(p,m-2)%mod;
			printf("%lld\n",f);
		}
		else {
			if(m==1){
				printf("1\n");
				continue;			
			}
			ll g=4*(power(4,n/2)+mod-1)%mod;
			g=g*power(3,mod-2)%mod;
			ll p=(power(2,n)+mod-1)%mod;
			ll f=g*(power(p,m-1)+mod-1)%mod;
			f=f*power((p+mod-1)%mod,mod-2)%mod;
			printf("%lld\n",(f+1)%mod);
		}
	}
}
