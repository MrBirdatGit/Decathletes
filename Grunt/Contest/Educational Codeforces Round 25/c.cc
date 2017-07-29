#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, k;
ll a[1050];
int main(){
	scanf("%lld%lld", &n, &k);
	for(ll i=1;i<=n;i++)scanf("%lld", &a[i]);
	sort(a+1, a+1+n);
	ll ans=0;
	for(ll i=1;i<=n;i++){
		while(2*k<a[i]){
			k*=2;
			ans++;
		}
		k=max(k, a[i]);
	}
	cout<<ans<<endl;
}

