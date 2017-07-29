//poj花式A,zoj花式wa
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 410;
const int maxm = maxn * maxn;
const int inf = 0x3f3f3f3f;
int n, m, tot, s, t;
int head[maxn], cur[maxn], h[maxn], que[maxm],in[maxn],id[maxn][maxn];
int lim[2][maxn][maxn];
struct edge { int to, next, cap; }e[maxm];
void init() {
	tot = 0;
	memset(head, -1, sizeof(head));
	memset(in,0,sizeof(in));
	memset(id,0,sizeof(id));
	memset(lim[0],0,sizeof(lim[0]));
	memset(lim[1],0x3f,sizeof(lim[1]));
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
		for (int i = 1; i <= t; i++)
			cur[i] = head[i];
		ret += dfs(s, inf);
	}
	return ret;
}
int main(){
//	freopen("a.in","r",stdin);
	int T;
	scanf("%d",&T);
	int c,x,y,z;
	char str[3];
	while(T--){
		scanf("%d%d",&m,&n);
		init();
		s = n + m + 1;
		t = s + 1;
		for(int i = 1;i<=m;i++){
			scanf("%d",&c);
			// c/c
			addedge(s,i,0);
			in[s] -= c;
			in[i] += c;
		}
		for(int i = 1;i<=n;i++){
			scanf("%d",&c);
			addedge(m+i,t,0);
			in[m+i] -= c;
			in[t] += c;
		}
		scanf("%d",&c);
		while(c--){
			scanf("%d%d%s%d",&x,&y,str,&z);
			int i1,i2,j1,j2;
			if(x == 0){
				i1 = 1;i2 = m;
			}else
				i1 = i2 =x;
			if(y == 0){
				j1 = 1;j2 = n;
			}else
				j1 = j2 = y;
			for(int i = i1;i<=i2;i++){
				for(int j = j1;j<=j2;j++){
					if(str[0] == '>'){
						lim[0][i][j] = max(lim[0][i][j],z+1);
					}else if(str[0] == '<'){
						lim[1][i][j] = min(lim[1][i][j],z-1);
					}else{
						lim[0][i][j] = max(lim[0][i][j],z);
						lim[1][i][j] = min(lim[1][i][j],z);
					}
				}
			}

		}
		bool flag = 0;
		for(int i = 1;i<=m;i++){
			for(int j = 1;j<=n;j++){
				if(lim[0][i][j] > lim[1][i][j]){						
					flag = 1;
					break;
				}
				addedge(i,j+m,lim[1][i][j] - lim[0][i][j]);
				id[i][j] = tot-1;
				in[i] -= lim[0][i][j];
				in[m+j] += lim[0][i][j];
			}
			if(flag) break;
		}
		if(flag){
			printf("IMPOSSIBLE\n");
			continue;
		}
		addedge(t,s,inf);
		int num = t;
		s += 2;t += 2;
        int sum = 0;
		for(int i  = 1;i<=num;i++){
			if(in[i] > 0){
				addedge(s,i,in[i]);
				sum += in[i];
			}else
				addedge(i,t,-in[i]);
		}
		if(dinic() != sum){
			printf("IMPOSSIBLE\n\n");
			continue;
		}
		for(int i = 1;i<=m;i++){
			for(int j = 1;j<=n;j++) {
				printf("%d%c",lim[0][i][j]+e[id[i][j]].cap,j == n?'\n':' ');
			}
		}
	}
}

