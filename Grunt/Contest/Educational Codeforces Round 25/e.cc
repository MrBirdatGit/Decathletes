#include <bits/stdc++.h>
using namespace std;

struct Edge{
	int to, next;
}e[105000];

int cnt;
int head[105000];
int degree[105000];
int ans[105000];

void add(int v, int u){
	e[cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt++;
	degree[v]++;
}

void init(){
	cnt=0;
	memset(head, -1, sizeof(head));
	memset(degree, 0, sizeof(degree));
}

int n, m;
priority_queue<int>pq;

int main(){
	init();
	scanf("%d%d", &n, &m);
	for(int i=1;i<=m;i++){
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
	}
	for(int i=1;i<=n;i++){
		if(!degree[i])pq.push(i);
	}
	int cnt=0;
	while(!pq.empty()){
		int tmp=pq.top();
		pq.pop();
		++cnt;
		ans[tmp]=n+1-cnt;
		for(int i=head[tmp];~i;i=e[i].next){
			degree[e[i].to]--;
			if(!degree[e[i].to])pq.push(e[i].to);
		}
	}
	for(int i=1;i<=n;i++)printf("%d%c", ans[i], i==n?'\n':' ');
}

