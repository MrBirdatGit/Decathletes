//注意点的标号从0开始
int n, m, tot, s, t;
int head[maxn], cur[maxn], h[maxn], que[maxn];
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