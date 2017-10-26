const int maxn = 100010;//点数的最大值
const int maxm = 400010;//边数的最大值
const int INF = 0x3f3f3f3f;
struct edge {
	int to, next, cap, flow;
}e[maxm];
int tol;
int head[maxn];
int gap[maxn], dep[maxn], cur[maxn];
void init() {
	tol = 0;
	memset(head, -1, sizeof(head));
}
void addedge(int u, int v, int w, int rw = 0) {
	e[tol].to = v; e[tol].cap = w; e[tol].flow = 0;
	e[tol].next = head[u]; head[u] = tol++;
	e[tol].to = u; e[tol].cap = rw; e[tol].flow = 0;
	e[tol].next = head[v]; head[v] = tol++;
}
int Q[maxn];
void bfs(int s, int t) {
	memset(dep, -1, sizeof(dep));
	memset(gap, 0, sizeof(gap));
	gap[0] = 1;
	int front = 0, rear = 0;
	dep[t] = 0;
	Q[rear++] = t;
	while (front != rear) {
		int u = Q[front++];
		for (int i = head[u]; i != -1; i = e[i].next) {
			int v = e[i].to;
			if (dep[v] != -1)continue;
			Q[rear++] = v;
			dep[v] = dep[u] + 1;
			gap[dep[v]]++;
		}
	}
}
int S[maxn];
int sap(int s, int t, int N) {
	bfs(s, t);
	memcpy(cur, head, sizeof(head));
	int top = 0;
	int u = s;
	int ans = 0;
	while (dep[s] < N) {
		if (u == t) {
			int Min = INF;
			int inser;
			for (int i = 0; i < top; i++)
				if (Min > e[S[i]].cap - e[S[i]].flow) {
					Min = e[S[i]].cap - e[S[i]].flow;
					inser = i;
				}
			for (int i = 0; i < top; i++) {
				e[S[i]].flow += Min;
				e[S[i] ^ 1].flow -= Min;
			}
			ans += Min;
			top = inser;
			u = e[S[top] ^ 1].to;
			continue;
		}
		bool flag = false;
		int v;
		for (int i = cur[u]; i != -1; i = e[i].next) {
			v = e[i].to;
			if (e[i].cap - e[i].flow && dep[v] + 1 == dep[u]) {
				flag = true;
				cur[u] = i;
				break;
			}
		}
		if (flag) {
			S[top++] = cur[u];
			u = v;
			continue;
		}
		int Min = N;
		for (int i = head[u]; i != -1; i = e[i].next)
			if (e[i].cap - e[i].flow && dep[e[i].to] < Min) {
				Min = dep[e[i].to];
				cur[u] = i;
			}
		gap[dep[u]]--;
		if (!gap[dep[u]])return ans;
		dep[u] = Min + 1;
		gap[dep[u]]++;
		if (u != s) u = e[S[--top] ^ 1].to;
	}
	return ans;
}
int main() {
	int n, m, u, v, cost;
	while (~scanf("%d%d", &n, &m)) {
		init();
		for (int i = 0; i<m; i++) {
			scanf("%d%d%d", &u, &v, &cost);
			addedge(u, v, cost);
		}
		printf("%d\n", sap(1, n, n));
	}
	return 0;
}