const int maxn = 100010;
const int maxm = 1000010;
const int inf = 0x3f3f3f3f;
struct Edge{
	int to,next,cap,flow,cost;	
}edge[maxm];
int head[maxn],tot;
int pre[maxn],dis[maxn];
bool vis[maxn];
int N;//注意！！！一般设置为t+1
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
}//返回最大流流量,cost为费用
