#include<bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;
int n, m, tot,s,t;
int head[205], cur[205], h[205], q[205], in[205];
int l[100005];
struct edge { int to, next, cap; }e[100005];
void init() {
	tot = 0;
	memset(head, -1, sizeof(head));
}
void addedge(int u, int v, int w) {
	e[tot].to = v; e[tot].next = head[u]; e[tot].cap = w; head[u] = tot++; 
	e[tot].to = u; e[tot].next = head[v]; e[tot].cap = 0; head[v] = tot++;
}
bool bfs() {
	memset(h,-1,sizeof(h));
	int tmp = 0, w = 1; q[s] = 0; h[s] = 0;
	while (tmp != w) {
		int now = q[tmp]; tmp++;
		for (int i = head[now]; i!=-1; i = e[i].next)
			if (e[i].cap&&h[e[i].to] == -1) {
				h[e[i].to] = h[now] + 1;
				q[w++] = e[i].to;
			}
	}
	if (h[t] == -1)return 0;
	return 1;
}
int dfs(int x, int f) {
	if (x == t)return f;
	int w, used = 0;
	for (int i = cur[x]; i!=-1; i = e[i].next)
		if (h[e[i].to] == h[x] + 1) {
			w = f - used; w = dfs(e[i].to, min(e[i].cap, w));
			e[i].cap -= w; if (e[i].cap)cur[x] = i; e[i ^ 1].cap += w;
			used += w; if (used == f)return f;
		}
	if (!used)h[x] = 1;
	return used;
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
int main() {
	int T, u, v, c;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		s = 0,t = n + 1;
		init();
		memset(in,0,sizeof(in));
		for (int i = 0; i<m; i++){
			scanf("%d%d%d%d", &u, &v, l + i, &c);
			addedge(u, v, c - l[i]);
			in[u] -= l[i];
			in[v] += l[i];
		}
		int sum = 0;
		for(int i = 1;i<=n;i++){
			if(in[i] > 0){
				addedge(s,i,in[i]);
				sum += in[i];
			}
			else addedge(i,t,-in[i]);
		}
		if(sum != dinic()){
			printf("NO\n\n");
			continue;
		}
		printf("YES\n");
		for(int i = 0;i<m;i++){
			printf("%d\n",e[i<<1|1].cap + l[i]);
		}
		printf("\n");
	}
}

