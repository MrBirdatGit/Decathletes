#include<bits/stdc++.h>
using namespace std;
const int maxn = 200010;
int a[maxn], b[maxn], c[maxn];
int head[maxn], tot;
struct edge{
	int to,next;
}e[200010];
void addedge(int u,int v){
	e[tot].to = v;
	e[tot].next = head[u];
	head[u] = tot++;
}
int dfn[maxn],low[maxn],stk[maxn],belong[maxn],top,ins[maxn],clk,scc;
int num[maxn];
void init(){
	memset(head,-1,sizeof(head));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(ins,0,sizeof(ins));
	tot = top = clk = scc = 0;
}
void Tarjan(int u){
	int v;
	dfn[u] = low[u] = ++clk;
	stk[top++] = u;
	ins[u] = 1;
	for(int i = head[u];i!=-1;i=e[i].next){
		int v = e[i].to;
		if(!dfn[v]){
			Tarjan(v);
			low[u] = min(low[u],low[v]);
		}else if(ins[v]){
			low[u] = min(low[u],dfn[v]);
		}
	}
	if(low[u] == dfn[u]){
		scc++;
		do{
			v = stk[--top];
			ins[v] = 0;
			belong[v] = scc;
			num[scc]++;
		}while(u != v);
	}
}
int n;
bool solve(int num){
	init();
	for(int i = 0;i<num;i++){
		if(c[i] == 0){
			addedge(a[i], b[i]+n);
			addedge(b[i], a[i]+n);
		}else if(c[i] == 1){
			addedge(a[i], b[i]);
			addedge(b[i], a[i]);
            addedge(a[i]+n, b[i]+n);
			addedge(b[i]+n, a[i]+n);
		}else{
			addedge(a[i]+n, b[i]);
			addedge(b[i]+n, a[i]);
		}
	}
	int t = n*2;
	for(int i = 0;i<t;i++){
		if(!dfn[i])
			Tarjan(i);
    }
	for(int i =0 ;i<n;i++){
		if(belong[i] == belong[i+n])
			return 0;
	}
	return 1;
}
int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		int m;
		scanf("%d%d", &n, &m);
		for(int i = 0;i<m;i++){
			scanf("%d%d%d", &a[i], &b[i], &c[i]);
		}
		int l = 1, r = m, ans;
		while(l<=r){
			int mid = (l + r)/2;
			if(solve(mid)){
				ans = mid;
				l = mid + 1;
			}else
				r = mid - 1;
		}
		printf("%d\n", ans);
	}
}