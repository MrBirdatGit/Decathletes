#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[205000];
map<ll,int>mp;
int n;
int main(){
	scanf("%d",&n);
	mp[0]=0;
	ll sum=0;
	ll M=1LL<<60;
	ll st=-1;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		sum+=a[i];
		if(mp.find(sum)==mp.end()){
			mp[sum]=i;
		}
		else {
			if(i-mp[sum]<M){
				M=i-mp[sum];
				st=mp[sum]+1;
				mp[sum]=i;
			}
		}
	}
	if(M==1LL<<60)printf("-1\n");
	else printf("%lld %lld\n",st,M);
	
}
