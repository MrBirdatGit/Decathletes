#include<bits/stdc++.h>
using namespace std;
const int maxn = 2010;
const int maxm = maxn * maxn;
const int inf = 0x3f3f3f3f;
int n, m, tot, s, t;
int head[maxn], cur[maxn], h[maxn], que[maxm],in[maxn],low[410][1100],id[410][1100];
struct edge { int to, next, cap; }e[1000000];
void init() {
	tot = 0;
	memset(head, -1, sizeof(head));
	memset(in,0,sizeof(in));
	memset(id,0,sizeof(id));
}
void addedge(int u, int v, int w) {
	e[tot].to = v; e[tot].next = head[u]; e[tot].cap = w; head[u] = tot++;
	e[tot].to = u; e[tot].next = head[v]; e[tot].cap = 0; head[v] = tot++;
}
bool bfs() {
	memset(h,-1,sizeof(h));
	int f = 0, ed = 1; que[0] = s; h[s] = 0;
	while (f != ed) {
		int now = que[f]; f++;
		for (int i = head[now]; i != -1; i = e[i].next)
			if (e[i].cap&&h[e[i].to] == -1) {
				h[e[i].to] = h[now] + 1;
				que[ed++] = e[i].to;
			}
	}
	if (h[t] == -1)return 0;
	return 1;
}
int dfs(int x, int f) {
	if (x == t)return f;
	int w, flow = 0;
	for (int i = cur[x]; i != -1; i = e[i].next)
		if (h[e[i].to] == h[x] + 1) {
			w = f - flow; w = dfs(e[i].to, min(e[i].cap, w));
			e[i].cap -= w; if (e[i].cap)cur[x] = i; e[i ^ 1].cap += w;
			flow += w; if (flow == f)return f;
		}
	if (!flow)h[x] = 1;
	return flow;
}                               
int dinic() {
	int ret = 0;
	while (bfs()) {
		for (int i = 0; i <= t; i++)
			cur[i] = head[i];
		ret += dfs(s, inf);
	}
	return ret;
}
int main(){
	//freopen("a.in","r",stdin);
	int n,m,g,c,d,l,r;
	while(~scanf("%d%d",&n,&m)){
		init();
		s = n + m;
		t = s + 1;
		for(int i = 0;i<m;i++){
			scanf("%d",&g);
            addedge(i+n,t,inf-g);
            in[i+n] -= g;
			in[t] += g;
		}
		for(int i = 0;i<n;i++){
			scanf("%d%d",&c,&d);
			addedge(s,i,d);
			for(int j  = 0;j<c;j++){
				scanf("%d%d%d",&g,&l,&r);
				addedge(i,g+n,r-l);
				in[i] -= l;
				in[g+n] += l;
				low[i][g] = l;
				id[i][g] = tot - 1;
			}
		}
		addedge(t,s,inf);
		int num = t;
		s += 2;t += 2;
        int sum = 0;
		for(int i  = 0;i<=num;i++){
			if(in[i] > 0){
				addedge(s,i,in[i]);
				sum += in[i];
			}else
				addedge(i,t,-in[i]);
		}
		if(dinic() != sum){
			printf("-1\n\n");
			continue;
		}
		head[s] = head[t] = -1;
		s -= 2;t -= 2;
		printf("%d\n",dinic());
		//之所以只需要再跑一次最大流，是因为第一次的流量储存在t->s中，第二次最大流会加上这一段的流量
		for(int i = 0;i<n;i++){
			for(int j = 0;j<m;j++) {
				if(id[i][j]){
					printf("%d\n",low[i][j] + e[id[i][j]].cap);
				}
			}
		}
        printf("\n");
	}
}
