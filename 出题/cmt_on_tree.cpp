#include<bits/stdc++.h>
using namespace std;
const int maxn = 100100;
struct edge{
	int v,next;
}e[maxn<<1];
int head[maxn],tote;
void addedge(int u,int v){
	e[++tote].v = v;
	e[tote].next = head[u];
	head[u] = tote;
}
int a[maxn];
int vis[maxn<<1],val[maxn<<1],bg[maxn],ed[maxn],clk;
void dfs(int u,int f){
	vis[++clk] = u;
	val[clk] = a[u];
	bg[u] = ed[u] = clk;
	for(int i = head[u];i;i=e[i].next){
		int v = e[i].v;
		if(v == f) continue;
		dfs(v,u);
		vis[++clk] = u;
		val[clk] = a[u];
		ed[u] = clk;
	}
}
int tot;
int rt[maxn*20],ls[maxn*20],rs[maxn*20],cnt[maxn*20];
void build(int &x,int l,int r){
	x = ++tot;
	cnt[x] = 0;
	if(l == r) return;
	int m = (l+r)>>1;
	build(ls[x],l,m);
	build(rs[x],m+1,r);
}
void update(int last,int &x,int l,int r,int p){
	x = ++tot;
	ls[x] = ls[last];
	rs[x] = rs[last];
	cnt[x] = cnt[last] + 1;
	if(l == r) return;
	int m = (l+r)>>1;
	if(p <= m) update(ls[last],ls[x],l,m,p);
	else update(rs[last],rs[x],m+1,r,p);
}
int query(int ll,int rr,int l,int r,int p){
	if(l == r){
		return cnt[rr] - cnt[ll];	
	}
	int ret = 0;
	int m = (l+r)>>1;
	if(p <= m) return query(ls[ll],ls[rr],l,m,p);
	else return cnt[ls[rr]] - cnt[ls[ll]] + query(rs[ll],rs[rr],m+1,r,p);
}
void print(int x,int l,int r){
	cout<<l<<' '<<r<<' '<<cnt[x]<<endl;
	if(l == r) return;
	int m = (l+r)>>1;
	print(ls[x],l,m);
	print(rs[x],m+1,r);
}
void init(){
	tot = etot = clk = 0;
	memset(head,0,sizeof(head));
}
int last[maxn<<1];
int main(){
	int n,u,v;
	scanf("%d",&n);
	init();
	for(int i = 1;i<=n;i++)
		scanf("%d",a+i);
	for(int i = 1;i<n;i++){
		scanf("%d%d",&u,&v);
		addedge(u,v);
		addedge(v,u);
	}	
	dfs(1,0);
	build(rt[0],0,tot);
	/*for(int i = 1;i<=clk;i++){
		cout<<vis[i]<<' ';
	}cout<<endl;
	for(int i = 1;i<=clk;i++){
		cout<<val[i]<<' ';
	}cout<<endl;*/
	for(int i  = 1;i<=clk;i++){
		update(rt[i-1],rt[i],0,clk,last[val[i]]);
		last[val[i]] = i;
	}
	/*for(int i = 1;i<=n;i++){
		printf("%d %d %d\n",i,bg[i],ed[i]);
		printf("%d\n",query(rt[bg[i]-1],rt[ed[i]],0,clk,bg[i]-1));
	}*/
	int q;
	scanf("%d",&q);
	while(q--){
		scanf("%d",&u);
		printf("%d\n",query(rt[bg[u]-1],rt[ed[u]],0,clk,bg[u]-1));
	}
}
