//构造题
//注意到要使答案最小，节点要尽量直接接在根上
//但是又考虑到只有k个叶子节点
//考虑把n-k个非叶子节点先建树，建树的border的size一定不大于k
//若新节点接在根节点上导致border的size比k大
//则应接在border上深度最小的一个点下，这样不会增加border的size
//用一个queue维护一下border即可
#include <bits/stdc++.h>
using namespace std;
int n, k;
int a[205000];
int b[205000];
int tot=0;
queue<int>que;

vector<int>g[205000];

int dep[205000];

int dfs(int u){
	if(u==1){
		int ma1=0, ma2=0;
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i];
			dfs(v);
			if(dep[v]>ma1){
				ma2=ma1;
				ma1=dep[v];
			}
			else if(dep[v]>ma2){
				ma2=dep[v];
			}
		}
		return ma1+ma2+2;
	}
	dep[u]=0;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		dfs(v);
		dep[u]=max(dep[v]+1, dep[u]);
	}
	return 0;
}

int main()
{
	scanf("%d%d", &n, &k);
	int m=n-k;
	int rsiz=2;
	int qsiz=0;
	for(int i=2;i<=m;i++){
		if(rsiz>0){
			rsiz--;
			que.push(i);
			qsiz++;
			a[++tot]=1;
			b[tot]=i;
		}
		else {
			if(qsiz<k){
				que.push(i);
				qsiz++;
				a[++tot]=1;
				b[tot]=i;
			}
			else {
				int tmp=que.front();
				que.pop();
				que.push(i);
				a[++tot]=tmp;
				b[tot]=i;
			}
		}
	}
	for(int i=m+1;i<=n;i++){
		if(rsiz||que.empty()){
			rsiz--;
			a[++tot]=1;
			b[tot]=i;
		}
		else {
			int tmp=que.front();
			que.pop();
			a[++tot]=tmp;
			b[tot]=i;
		}
	}
	for(int i=1;i<=tot;i++){
		g[a[i]].push_back(b[i]);
	}
	int totl=dfs(1);
	printf("%d\n", totl);
	for(int i=1;i<n;i++)printf("%d %d\n", a[i], b[i]);
}

