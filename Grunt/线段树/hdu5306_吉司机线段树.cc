//吉司机宇宙线段树之王！
#include <bits/stdc++.h>
using namespace std;
const int maxn=1000005;
typedef long long ll;

int mx[maxn<<2];
int cnt[maxn<<2];
int se[maxn<<2];
int lazy[maxn<<2];
ll sum[maxn<<2];
int a[maxn];
int n, m;

void putlazy(int u, int t){
	sum[u]-=1LL*cnt[u]*(mx[u]-t);
	mx[u]=t;
	lazy[u]=t;
}

void pushdown(int u){
	if(lazy[u]==-1)return;
	if(mx[2*u]>lazy[u]){
		sum[2*u]-=1LL*cnt[2*u]*(mx[2*u]-lazy[u]);
		mx[2*u]=lazy[u];
		lazy[2*u]=lazy[u];
	}
	if(mx[2*u+1]>lazy[u]){
		sum[2*u+1]-=1LL*cnt[2*u+1]*(mx[2*u+1]-lazy[u]);
		mx[2*u+1]=lazy[u];
		lazy[2*u+1]=lazy[u];

	}
	lazy[u]=-1;
}

void pushup(int u){
	if(mx[2*u]==mx[2*u+1]){
		mx[u]=mx[2*u];
		cnt[u]=cnt[2*u]+cnt[2*u+1];
		se[u]=max(se[2*u], se[2*u+1]);
		sum[u]=sum[2*u]+sum[2*u+1];
	}
	else if(mx[2*u]>mx[2*u+1]){
		mx[u]=mx[2*u];
		cnt[u]=cnt[2*u];
		se[u]=max(se[2*u], mx[2*u+1]);
		sum[u]=sum[2*u]+sum[2*u+1];
	}
	else {
		mx[u]=mx[2*u+1];
		cnt[u]=cnt[2*u+1];
		se[u]=max(mx[2*u], se[2*u+1]);
		sum[u]=sum[2*u]+sum[2*u+1];
	}
}

void build(int u, int l, int r){
	lazy[u]=-1;
	if(l==r){
		mx[u]=sum[u]=a[l];
		cnt[u]=1;
		se[u]=-1;
		return;
	}
	int mid=l+r>>1;
	build(2*u, l, mid);
	build(2*u+1, mid+1, r);
	pushup(u);
}

void update(int u, int ql, int qr, int t, int l, int r){
	if(ql>r||qr<l||mx[u]<=t)return;
	if(ql<=l&&r<=qr&&se[u]<t){
		putlazy(u, t);
		return;
	}
	pushdown(u);
	int mid=l+r>>1;
	update(2*u, ql, qr, t, l, mid);
	update(2*u+1, ql, qr, t, mid+1, r);
	pushup(u);
}

int getmx(int u, int ql, int qr, int l, int r){
	if(ql>r||qr<l)return 0;
	if(ql<=l&&r<=qr)return mx[u];
	pushdown(u);
	int mid=l+r>>1;
	int ans=0;
	ans=max(ans, getmx(2*u, ql, qr, l, mid));
	ans=max(ans, getmx(2*u+1, ql, qr, mid+1, r));
	return ans;
}

ll getsum(int u, int ql, int qr, int l, int r){
	if(ql>r||qr<l)return 0;
	if(ql<=l&&r<=qr)return sum[u];
	pushdown(u);
	int mid=l+r>>1;
	ll ans=0;
	ans+=getsum(2*u, ql, qr, l, mid);
	ans+=getsum(2*u+1, ql, qr, mid+1, r);
	return ans;
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		for(int i=1;i<=n;i++)scanf("%d", &a[i]);
		build(1, 1, n);
		for(int i=1;i<=m;i++){
			int tag;
			scanf("%d", &tag);
			if(tag==0){
				int x, y, t;
				scanf("%d%d%d", &x, &y, &t);
				update(1, x, y, t, 1, n);
			}
			else if(tag==1){
				int x, y;
				scanf("%d%d", &x, &y);
				printf("%d\n", getmx(1, x, y, 1, n));
			}
			else {
				int x, y;
				scanf("%d%d", &x, &y);
				printf("%lld\n", getsum(1, x, y, 1, n));
			}
		}
	}
}

