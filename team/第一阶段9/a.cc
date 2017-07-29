#include <bits/stdc++.h>
using namespace std;
int n, m;
int g[305][305];
bool vis[305][305];
int tag[305][305];
int ok;

int dirx[4]={1, 0, -1, 0};
int diry[4]={0, 1, 0, -1};

void dfs(int x, int y){
	vis[x][y]=true;
	if(!ok)return ;
	if(x<1||x>n||y<1||y>m){
		ok=false;
		return;
	}
	if(g[x][y]>=1){
		tag[x][y]=1;
		return;
	}
	for(int i=0;i<4;i++){
		int xt=x+dirx[i];
		int yt=y+diry[i];
		if(!vis[xt][yt])dfs(xt, yt);
	}
}

void dfs2(int x, int y){
	vis[x][y]=true;
	if(g[x][y]>=1&&tag[x][y]==1){
		tag[x][y]=2;
		return;
	}
	for(int i=0;i<4;i++){
		int xt=x+dirx[i];
		int yt=y+diry[i];
		if(xt>=0&&xt<=n+1&&yt>=0&&yt<=m+1&&!vis[xt][yt])dfs2(xt, yt);
	}
}

int main()
{
	while(~scanf("%d%d", &n, &m)){
		memset(g, 0, sizeof(g));
		memset(tag, 0, sizeof(tag));
		int x, y;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%d", &g[i][j]);
				if(g[i][j]==-1){
					x=i;y=j;
				}
			}
		}
		memset(vis, false, sizeof(vis));
		ok=true;
		dfs(x, y);
		if(!ok){
			printf("Ali Win\n");
		}
		else {
			memset(vis, false, sizeof(vis));
			dfs2(0, 0);
			int cut=0;
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++){
					if(g[i][j]<=0)continue;
					if(tag[i][j]==2){
						cut+=g[i][j]-1;
					}
					else if(tag[i][j]==0){
						cut+=g[i][j];
					}
				}
			}
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++)printf("%d ", tag[i][j]);
				printf("\n");
			}
			if(cut%2==0){
				printf("Baba Win\n");
			}
			else printf("Ali Win\n");
		}
	}
}

