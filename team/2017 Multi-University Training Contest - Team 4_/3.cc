#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;

bool vis[1050000];
int prime[1050000];
int tot;

void init(){
	memset(vis,false,sizeof(vis));
	tot=0;
	for(int i=2;i<=1000000;i++){
		if(!vis[i]){
			prime[++tot]=i;
			for(int j=2;j*i<=1000000;j++){
				vis[j*i]=true;
			}
		}
	}
}

ll l,r,k;

ll res[1050000];
ll ans[1050000];


int main(){
	init();
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld%lld",&l,&r,&k);
		for(ll i=l;i<=r;i++){
			res[i-l]=i;
			ans[i-l]=1;
		}
		for(ll i=1;i<=tot;i++){
			ll p=prime[i];
			ll j=l/p*p;
			if(j<l){
				j+=p;
			}
			for(;j<=r;j+=p){
				ll cnt=1;
				while(res[j-l]%p==0){
					res[j-l]/=p;
					cnt+=k;
				}
				cnt%=mod;
				ans[j-l]=ans[j-l]*cnt%mod;
			}
		}
		ll sum=0;
		for(ll i=l;i<=r;i++){
			if(res[i-l]!=1)ans[i-l]=ans[i-l]*(1+k)%mod;
			sum=(sum+ans[i-l])%mod;
		}
		printf("%lld\n",sum);
	}
}
