#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,k;
ll ans;
struct edge{
	int to,v;
};
vector<edge>g[1050000];
int siz[1050000];
void dfs(int u,int from){
	siz[u]=1;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i].to;
		int w=g[u][i].v;
		if(v!=from){
			dfs(v,u);
			siz[u]+=siz[v];
			ans+=w*min(k,siz[v]);
		}
	}
}
int main(){
	while(~scanf("%d%d",&n,&k)){
		for(int i=1;i<=n;i++)g[i].clear();
		for(int i=1;i<n;i++){
			int x,y,w;
			scanf("%d%d%d",&x,&y,&w);
			g[x].push_back((edge){y,w});
			g[y].push_back((edge){x,w});
		}
		ans=0;
		dfs(1,0);
		printf("%lld\n",ans);
	}
}
