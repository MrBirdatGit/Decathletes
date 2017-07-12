#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn = 100010;
const int maxm = 1000010;
const int inf = 0x3f3f3f3f;
struct Edge{
	int to,next,cap,flow,cost;	
}edge[maxm];
int head[maxn],tot;
int pre[maxn],dis[maxn];
bool vis[maxn];
int N;
void init(){
	tot = 0;
	memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int cap,int cost){
	edge[tot].to = v;
	edge[tot].cap = cap;
	edge[tot].cost = cost;
	edge[tot].flow = 0;
	edge[tot].next = head[u];
	head[u] = tot++;
	edge[tot].to = u;
	edge[tot].cap = 0;
	edge[tot].cost = -cost;
	edge[tot].flow = 0;
	edge[tot].next = head[v];
	head[v] = tot++;
}
int spfa(int s,int t){
	queue<int>q;
	for(int i = 0;i<N;i++){
		dis[i] = inf;
		vis[i] = 0;
		pre[i] = -1;
	}
	dis[s] = 0;
	vis[s] = 1;
	q.push(s);
	while(!q.empty()){
		int u = q.front();q.pop();
		vis[u] = 0;
		for(int i = head[u];i!=-1;i = edge[i].next){
			int v = edge[i].to;
			if(edge[i].cap > edge[i].flow && dis[v] > dis[u] + edge[i].cost){
				dis[v] = dis[u] + edge[i].cost;
				pre[v] = i;
				if(!vis[v]){
					vis[v] = 1;
					q.push(v);
				}
			}
		}
	}
	if(pre[t] == -1) return 0;
	return 1;
}
int MCMF(int s, int t, int &cost) {
	int flow = 0;
	cost = 0;
	while (spfa(s, t)) {
		int Min = inf;
		for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]) {
			if (Min > edge[i].cap - edge[i].flow)
				Min = edge[i].cap - edge[i].flow;
		}
		for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]) {
			edge[i].flow += Min;
			edge[i ^ 1].flow -= Min;
			cost += edge[i].cost * Min;
		}
		flow += Min;
	}
	return flow;
}
int a[210],b[210],c[210];
vector<int>hs;
int main(){
	int T,n,k;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		hs.clear();
		init();
		for(int i = 0;i<n;i++){
			scanf("%d%d%d",a+i,b+i,c+i);
			hs.push_back(a[i]);
			hs.push_back(b[i]);
		}
		sort(hs.begin(),hs.end());
		hs.erase(unique(hs.begin(),hs.end()),hs.end());
		int sz = hs.size();
		int s = sz,t = s+1;
		int res = 0;
		addedge(s,0,k,0);
		addedge(sz-1,t,k,0);
		for(int i = 0;i<sz-1;i++){
			addedge(i,i+1,inf,0);
		}
		for(int i = 0;i<n;i++){
			int p1 = lower_bound(hs.begin(),hs.end(),a[i]) - hs.begin();
			int p2 = lower_bound(hs.begin(),hs.end(),b[i]) - hs.begin();
			addedge(p1,p2,1,-c[i]);
		}
		int cost = 0;
		N = t+1;
		MCMF(s,t,cost);
		printf("%d\n",-cost);
	}
}
