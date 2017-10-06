#include <bits/stdc++.h>
using namespace std;
const int maxn=10500;

int dep[maxn],siz[maxn],fa[maxn],id[maxn],son[maxn],val[maxn],top[maxn];
int num,n;
int ma[maxn<<2];
vector<int>g[maxn];
struct edge{
	int x,y,val;
	void read(){
		scanf("%d%d%d",&x,&y,&val);
	}
}e[maxn];

void init(){
	for(int i=1;i<=n;i++)g[i].clear();
}

void dfs1(int u,int f,int d){
	dep[u]=d,siz[u]=1,son[u]=0,fa[u]=f;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==f)continue;
		dfs1(v,u,d+1);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])son[u]=v;
	}
}

void dfs2(int u,int tp){
	top[u]=tp;
	id[u]=++num;
	if(son[u])dfs2(son[u],tp);
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}

void pushup(int u){
	ma[u]=max(ma[2*u],ma[2*u+1]);
}

void build(int u,int l,int r){
	if(l==r){
		ma[u]=val[l];
		return ;
	}	
	int mid=(l+r)/2;
	build(2*u,l,mid);
	build(2*u+1,mid+1,r);
	pushup(u);
}

void update(int u,int p,int l,int r,int q){
	if(p<l||p>r)return;
	if(l==r){
		ma[u]=q;
		return;
	}
	int mid=(l+r)/2;
	update(2*u,p,l,mid,q);
	update(2*u+1,p,mid+1,r,q);
	pushup(u);
}

int query(int u,int ql,int qr,int l,int r){
	if(ql>r||qr<l)return 0;
	if(ql<=l&&r<=qr)return ma[u];
	int mid=(l+r)/2;
	return max(query(2*u,ql,qr,l,mid),query(2*u+1,ql,qr,mid+1,r));
}


int Query(int u,int v){
	int ret=0;
	int tp1=top[u],tp2=top[v];
	while(tp1!=tp2){
		if(dep[tp1]<dep[tp2]){
			swap(u,v);swap(tp1,tp2);
		}
		ret=max(ret,query(1,id[tp1],id[u],1,num));
		u=fa[tp1];
		tp1=top[u];
	}
	if(u==v)return ret;
	if(dep[u]<dep[v])swap(u,v);
	ret=max(ret,query(1,id[son[v]],id[u],1,num));
	return ret;
}




int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		init();
		for(int i=1;i<n;i++){
			e[i].read();
			g[e[i].x].push_back(e[i].y);
			g[e[i].y].push_back(e[i].x);
		}
		num=0;
		dfs1(1,0,1);
		dfs2(1,1);
		for(int i=1;i<n;i++){
			if(dep[e[i].x]<dep[e[i].y])swap(e[i].x,e[i].y);
			val[id[e[i].x]]=e[i].val;
		}
		build(1,1,num);
		char tag[30];
		while(scanf("%s",tag)){
			if(tag[0]=='D')break;
			if(tag[0]=='Q'){
				int x,y;
				scanf("%d%d",&x,&y);
				printf("%d\n",Query(x,y));
			}
			else {
				int pos,x;
				scanf("%d%d",&pos,&x);
				update(1,id[e[pos].x],1,num,x);
			}
		}
	}
}
