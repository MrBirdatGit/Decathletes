//吉司机线段树
//牛逼啊
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=300005;

int n, m;
ll mn[maxn<<2];
int cnt[maxn<<2];
ll se[maxn<<2];
ll lzcut[maxn<<2];
ll lzadd[maxn<<2];
int a[maxn];

void putcut(int u, ll c){
	mn[u]=c;
	lzcut[u]=c;
}

void putadd(int u, ll c){
	lzadd[u]+=c;
	if(lzcut[u]!=-1)lzcut[u]+=c;
	mn[u]+=c;
	if(se[u]!=-1)se[u]+=c;
}

void pushdown(int u){
	if(lzadd[u]){
		putadd(2*u, lzadd[u]);
		putadd(2*u+1, lzadd[u]);
		lzadd[u]=0;
	}
	if(lzcut[u]!=-1){
		if(mn[2*u]<lzcut[u]){
			mn[2*u]=lzcut[u];
			lzcut[2*u]=lzcut[u];
		}
		if(mn[2*u+1]<lzcut[u]){
			mn[2*u+1]=lzcut[u];
			lzcut[2*u+1]=lzcut[u];
		}
		lzcut[u]=-1;
	}
}

void pushup(int u){
	if(mn[2*u]==mn[2*u+1]){
		mn[u]=mn[2*u];
		cnt[u]=cnt[2*u]+cnt[2*u+1];
		if(se[2*u]==-1&&se[2*u+1]==-1)se[u]=-1;
		else if(se[2*u]==-1)se[u]=se[2*u+1];
		else if(se[2*u+1]==-1)se[u]=se[2*u];
		else se[u]=min(se[2*u], se[2*u+1]);
	}
	else if(mn[2*u]<mn[2*u+1]){
		mn[u]=mn[2*u];
		cnt[u]=cnt[2*u];
		if(se[2*u]==-1){
			se[u]=mn[2*u+1];
		}
		else {
			se[u]=min(mn[2*u+1], se[2*u]);
		}
	}
	else {
		mn[u]=mn[2*u+1];
		cnt[u]=cnt[2*u+1];
		if(se[2*u+1]==-1){
			se[u]=mn[2*u];
		}
		else {
			se[u]=min(mn[2*u], se[2*u+1]);
		}
	}
}

void build(int u, int l, int r){
	lzcut[u]=-1;
	lzadd[u]=0;
	if(l==r){
		mn[u]=a[l];
		cnt[u]=1;
		se[u]=-1;
		return;
	}
	int mid=(l+r)/2;
	build(2*u, l, mid);
	build(2*u+1, mid+1, r);
	pushup(u);
}

void cover(int u, int ql, int qr, int c, int l, int r){
	if(r<ql||qr<l)return;
	if(ql<=l&&r<=qr&&se[u]==-1){
		putadd(u, (ll)c-mn[u]);
		return;
	}
	int mid=(l+r)/2;
	pushdown(u);
	cover(2*u, ql, qr, c, l, mid);
	cover(2*u+1, ql, qr, c, mid+1, r);
	pushup(u);
}

void add(int u, int ql, int qr, int c, int l, int r){
	if(r<ql||qr<l||(se[u]==-1&&mn[u]==0&&c<=0))return;
	if(ql<=l&&r<=qr){
		if(mn[u]+c>=0){
			putadd(u, c);
			return;
		}
		else if(se[u]==-1||se[u]+c>0){
			putadd(u, c);
			putcut(u, 0);
			return;
		}
	}
	int mid=(l+r)/2;
	pushdown(u);
	add(2*u, ql, qr, c, l, mid);
	add(2*u+1, ql, qr, c, mid+1, r);
	pushup(u);
}

int query(int u, int ql, int qr, int l, int r){
	if(r<ql||qr<l)return 0;
	if(ql<=l&&r<=qr){
		if(mn[u]==0)return cnt[u];
		return 0;
	}
	int mid=(l+r)/2;
	int ret=0;
	pushdown(u);
	ret+=query(2*u, ql, qr, l, mid);
	ret+=query(2*u+1, ql, qr, mid+1, r);
	return ret;
}


int main(){
	scanf("%d%d", &n, &m);
	for(int i=1;i<=n;i++){
		scanf("%d", &a[i]);
	}
	build(1, 1, n);
	for(int i=1;i<=m;i++){
		int tag;
		scanf("%d", &tag);
		if(tag==1){
			int l, r, c;
			scanf("%d%d%d", &l, &r, &c);
			cover(1, l, r, c, 1, n);
		}
		else if(tag==2){
			int l, r, c;
			scanf("%d%d%d", &l, &r, &c);
			add(1, l, r, c, 1, n);
		}
		else {
			int l, r;
			scanf("%d%d", &l, &r);
			printf("%d\n", query(1, l, r, 1, n));
		}
	}
}

