#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
int val[maxn],h[maxn],N;
int getid(int x){
	return lower_bound(h+1,h+N+1,x)-h;
}
int root[maxn*20],ls[maxn*20],rs[maxn*20],cnt[maxn*20];
struct CMT{
	int tot;
	void init(){tot = 0;}
	void build(int l,int r,int &rt){
		rt = ++tot;
		cnt[rt] = 0;
		int m = (l+r)>>1;
		if(l == r) return;
		build(l,m,ls[rt]);
		build(m+1,r,rs[rt]);
	}
	void update(int last,int l,int r,int &rt,int p){
		rt = ++tot;
		ls[rt] = ls[last];
		rs[rt] = rs[last];
		cnt[rt] = cnt[last]+1;
		if(l == r) return;
		int m = (l+r)>>1;
		if(p<=m) update(ls[last],l,m,ls[rt],p);
		else update(rs[last],m+1,r,rs[rt],p);
	}
	int query(int ll,int rr,int p,int pp,int l,int r,int k){
		if(l == r) return l;
		int c = cnt[ls[ll]] + cnt[ls[rr]] - cnt[ls[p]] - cnt[ls[pp]];
		int m = (l+r)>>1;
		if(k <= c) return query(ls[ll],ls[rr],ls[p],ls[pp],l,m,k);
		else return query(rs[ll],rs[rr],rs[p],rs[pp],m+1,r,k-c);
	}
	void print(int l,int r,int rt){
		cout<<l<<' '<<r<<' '<<cnt[rt]<<endl;
		if(l == r) return;
		int m = (l+r)>>1;
		print(l,m,ls[rt]);
		print(m+1,r,rs[rt]);
	}
}cmt;
struct edge{
	int v,next;
}e[maxn<<1];
int head[maxn],tot,clk;
void addedge(int u,int v){
	e[++tot].v = v;
	e[tot].next = head[u];
	head[u] = tot;
}
void init(){
	tot = clk = 0;
	memset(head,0,sizeof(head));
}
int dep[maxn<<1],vs[maxn<<1],id[maxn],fa[maxn];
void dfs(int u,int p,int d){
	fa[u] = p;
	id[u] = clk;
	vs[clk] = u;
	dep[clk++] = d;
	cmt.update(root[p],1,N,root[u],getid(val[u]));
	for(int i = head[u];i;i=e[i].next){
		int v = e[i].v;
		if(v==p) continue;
		dfs(v,u,d+1);
		vs[clk] = u;
		dep[clk++] = d;
	}
}
int d[maxn<<1][30],idx[maxn<<1][30];
void rmq_init(int *a,int n){
	for(int i = 0;i<n;i++){
		d[i][0] = a[i];
		idx[i][0] = i;
	}
	for(int j = 1;(1<<j)<n;j++)
		for(int i = 0;i+(1<<j)-1<n;i++)
			if(d[i][j-1] < d[i+(1<<(j-1))][j-1]){
				d[i][j] = d[i][j-1];
				idx[i][j] = idx[i][j-1];
			}else{
				d[i][j] = d[i+(1<<(j-1))][j-1];
				idx[i][j] = idx[i+(1<<(j-1))][j-1];
			}
}
int rmq(int l,int r){
	int k = 0;
	while((1<<(k+1)) <= r - l + 1) k++;
	return d[l][k]<d[r-(1<<k)+1][k]?idx[l][k]:idx[r-(1<<k)+1][k];
}
int lca(int u,int v){
	return vs[rmq(min(id[u],id[v]),max(id[u],id[v]))];
}
int main(){
	int n,m,u,v,k;
	while(~scanf("%d%d",&n,&m)){
		for(int i = 1;i<=n;i++){
			scanf("%d",val+i);
			h[i] = val[i];
		}
		sort(h+1,h+n+1);
		N = unique(h+1,h+n+1)-h-1;
		init();
		cmt.init();
		cmt.build(1,N,root[0]);
		for(int i = 1;i<n;i++){
			scanf("%d%d",&u,&v);
			addedge(u,v);
			addedge(v,u);
		}
		dfs(1,0,0);
		rmq_init(dep,2*n-1);
		while(m--){
			scanf("%d%d%d",&u,&v,&k);
			int p = lca(u,v);
			printf("%d\n",h[cmt.query(root[u],root[v],root[p],root[fa[p]],1,N,k)]);
		}
	}
}
