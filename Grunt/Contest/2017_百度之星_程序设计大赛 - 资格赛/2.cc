#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll g[3050][3050];
bool vis[3050];
int n,m;

void dfs(int u){
	vis[u]=true;
	for(int i=1;i<=n;i++){
		if(u==i)continue;
		if(g[u][i]&&!vis[i])dfs(i);
	}
}

int main(){
	while(~scanf("%d%d",&n,&m)){
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)g[i][j]=0;
		for(int i=1;i<=n;i++)vis[i]=false;
		//memset(g,0,sizeof(g));
		//memset(vis,false,sizeof(vis));
		for(int i=1;i<=m;i++){
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			g[u][v]+=w;
			g[v][u]+=w;
		}
		dfs(1);
		bool ok=true;
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				ok=false;
				break;
			}
		}
		if(!ok)printf("0\n");
		else {
			ll M=1LL<<60;
			for(int i=1;i<=n;i++){
				ll tmp=0;
				for(int j=1;j<=n;j++){
					if(i==j)continue;
					tmp+=g[i][j];
				}
				M=min(M,tmp);
			}
			printf("%I64d\n",M);
		}
	}
}
