#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m;
ll t[205000];
ll b[205000];
int main(){
	scanf("%d%d", &n, &m);
	for(int i=1;i<=n;i++){
		scanf("%lld", &t[i]);
	}
	for(int i=1;i<=m;i++){
		scanf("%lld", &b[i]);
	}
	ll ans=0;
	if(b[1]<t[1])ans+=(t[1]-b[1])*2;
	if(b[m]>t[n])ans+=(b[m]-t[n])*2;
	for(int i=1;i<n;i++){
		ll tmp=t[i+1]-t[i];
		ll st=upper_bound(b+1, b+1+m, t[i])-b;
		ll ed=lower_bound(b+1, b+1+m, t[i+1])-b-1;
		if(st>m)break;
		if(st>ed)continue;
		tmp=min(tmp, 2*(t[i+1]-b[st]));
		tmp=min(tmp, 2*(b[ed]-t[i]));
		for(int j=st;j<ed;j++){
			tmp=min(tmp, 2*(b[j]-t[i])+2*(t[i+1]-b[j+1]));
		}
		ans+=tmp;
	}
	cout<<ans<<endl;
}

