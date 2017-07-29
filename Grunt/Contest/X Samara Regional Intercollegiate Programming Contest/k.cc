#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct node {
	ll v, c, from;
};
bool operator<(const node& a, const node& b){
	if(a.v==b.v)return a.c>b.c;
	return a.v<b.v;
}
struct seg{
	ll l, r, v, id;
}rec[205000];
bool operator<(const seg& a, const seg& b){
	return a.r<b.r;
}

int n;
node dp[205000];
ll ans[205000];
ll ri[205000];
int tot=0;

int main(){
	scanf("%d", &n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld", &rec[i].l, &rec[i].r, &rec[i].v);
		rec[i].id=i;
	}
	sort(rec+1, rec+1+n);
	for(int i=1;i<=n;i++)ri[i]=rec[i].r;
	dp[-1]=(node){0, 0, 0};
	for(int i=1;i<=n;i++){
		dp[i]=dp[i-1];
		ll l=rec[i].l;
		int ed=upper_bound(ri+1, ri+1+n, l)-ri-1;
		node tmp;
		tmp.v=rec[i].v+dp[ed].v;
		tmp.c=rec[i].r-rec[i].l+dp[ed].c;
		tmp.from=i;
		if(dp[i]<tmp)dp[i]=tmp;
	}
	//for(int i=0;i<=n;i++)printf("%lld\n", dp[i].v);
	ll v=dp[n].v, c=dp[n].c;
	ll now=dp[n].from;
	while(now){
		ans[++tot]=rec[now].id;
		int ed=upper_bound(ri+1, ri+1+n, rec[now].l)-ri-1;
		now=dp[ed].from;
	}
	sort(ans+1, ans+1+tot);
	printf("%d %lld %lld\n", tot, v, c);
	for(int i=1;i<=tot;i++)printf("%lld%c", ans[i], i==tot?'\n':' ');
}

