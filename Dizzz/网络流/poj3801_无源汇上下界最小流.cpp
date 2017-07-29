#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cstdlib>
#include<algorithm>

using namespace std;
const int maxn = 2010;
const int maxm = maxn * maxn;
const int inf = 0x3f3f3f3f;
int n, m, tot, s, t;
int head[maxn], cur[maxn], h[maxn], que[maxm],in[maxn];
struct edge { int to, next, cap; }e[1000000];
void init() {
	tot = 0;
	memset(head, -1, sizeof(head));
	memset(in,0,sizeof(in));
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
int getnum(char* str){
	if(str[0] == '+') return s;
	if(str[0] == '-') return t;
	int len = strlen(str);
	int ret = 0;
	for(int i = 0;i<len;i++){
		ret *= 10;
		ret += str[i]-'0';
	}
	return ret;
}
int main(){
	//freopen("a.in","r",stdin);
	char s1[5],s2[5];
	int a,b,c;
	while(~scanf("%d%d",&n,&m)){
		if(n + m == 0) break;
		init();
		s = n + 1;
		t = s + 1;
		for(int i = 0;i<m;i++){
			scanf("%s%s%d",s1,s2,&c);
            a = getnum(s1);
			b = getnum(s2);
			addedge(a,b,inf-c);
			in[a] -= c;
			in[b] += c;
		}
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
		addedge(t-2,s-2,inf);
		if(dinic() != sum){
			printf("impossible\n");
			continue;
		}
		printf("%d\n",e[tot-1].cap);
	}
}

