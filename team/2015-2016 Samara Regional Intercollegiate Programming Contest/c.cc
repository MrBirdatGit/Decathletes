#include <bits/stdc++.h>
using namespace std;
const int maxn=105000;

multiset<int>e[maxn];

inline void add(int u,int v){
	e[u].insert(v);
}

int degree[maxn];
bool vis[maxn];
int n,m;

vector<int>g[maxn];
int odd[maxn];
int id[maxn];
int vs[maxn];
int ans[maxn<<2];
int tot=0;
int vstot=0;
int len=0;
int st=0;

void dfs(int u){
	vis[u]=true;
	if(degree[u]%2==1){
		odd[tot]++;
	}
	g[tot].push_back(u);
	for(multiset<int>::iterator it=e[u].begin();it!=e[u].end();it++){
		int to=*it;
		if(!vis[to])dfs(to);
	}
}

bool cmp(int a,int b){
	return odd[a]<odd[b];
}

void edfs(int u){
	while(!e[u].empty()){
		multiset<int>::iterator it=e[u].begin();
		int to=*it;
		multiset<int>::iterator it1=e[to].lower_bound(u);
		e[u].erase(it);
		e[to].erase(it1);
		edfs(to);
	}
	ans[++len]=u;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
		degree[u]++;
		degree[v]++;		
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]&&degree[i]){
			tot++;
			id[tot]=tot;
			dfs(i);
		}
	}
	sort(id+1,id+1+tot,cmp);
	if(tot==1){
		;
	}
	else if(tot==2){
		int u=g[1][0];
		for(int i=0;i<g[1].size();i++){
			if(degree[g[1][i]]%2)u=g[1][i];
		}
		int v=g[2][0];
		for(int i=0;i<g[2].size();i++){
			if(degree[g[2][i]]%2)v=g[2][i];
		}
		add(u,v);
		add(v,u);
		degree[u]++;
		degree[v]++;
	}
	else {
		int u=g[id[1]][0];
		for(int i=0;i<g[id[1]].size();i++){
			if(degree[g[id[1]][i]]%2)u=g[id[1]][i];
		}
		int v=g[id[3]][0];
		for(int i=0;i<g[id[3]].size();i++){
			if(degree[g[id[3]][i]]%2)v=g[id[3]][i];
		}
		add(u,v);
		add(v,u);
		degree[u]++;
		degree[v]++;
		for(int i=3;i<tot;i++){
			int u=g[id[i]][0];
			for(int j=0;j<g[id[i]].size();j++){
				if(degree[g[id[i]][j]]%2)u=g[id[i]][j];
			}
			int v=g[id[i+1]][0];
			for(int j=0;j<g[id[i+1]].size();j++){
				if(degree[g[id[i+1]][j]]%2)v=g[id[i+1]][j];
			}
			add(u,v);
			add(v,u);
			degree[u]++;
			degree[v]++;
		}
		u=g[id[2]][0];
		for(int i=0;i<g[id[2]].size();i++){
			if(degree[g[id[2]][i]]%2)u=g[id[2]][i];
		}
		v=g[id[tot]][0];
		for(int i=0;i<g[id[tot]].size();i++){
			if(degree[g[id[tot]][i]]%2)v=g[id[tot]][i];
		}
		add(u,v);
		add(v,u);
		degree[u]++;
		degree[v]++;
	}
	for(int i=1;i<=n;i++)if(degree[i]%2){
		vs[++vstot]=i;
	}
	for(int i=1;i<=n;i++)if(degree[i])st=i;	
	for(int i=3;i<=vstot;i+=2){
		add(vs[i],vs[i+1]);
		add(vs[i+1],vs[i]);
		degree[vs[i]]++;
		degree[vs[i+1]]++;
	}
	if(vstot==0)edfs(st);
	else edfs(vs[1]);
	printf("%d\n",len);
	for(int i=1;i<=len;i++)printf("%d%c",ans[i],i==len?'\n':' ');
}
