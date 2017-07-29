#include <bits/stdc++.h>
using namespace std;

struct Edge{
	int to, next;
}e[2050000];

int cnt;
int head[1050000];

void init(){
	cnt=0;
	memset(head, -1, sizeof(head));
}

void add(int u, int v){
	e[cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt++;
}

int n, q;
int last;
int rt;
int lmin[1050000];
int M;

void dfs(int u, int from, int now){
	lmin[u]=min(now, u);
	for(int i=head[u];~i;i=e[i].next){
		if(e[i].to!=from)dfs(e[i].to, u, lmin[u]);
	}
}

int main(){
	init();
	scanf("%d%d", &n, &q);
	for(int i=1;i<n;i++){
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}

	int t, z;

	scanf("%d%d", &t, &z);
	rt=z%n+1;

	dfs(rt, 0, 1050000);

	M=1050000;
	last=0;

	for(int i=2;i<=q;i++){
		scanf("%d%d", &t, &z);
		z=(z+last)%n+1;
		if(t==1){
			M=min(M, lmin[z]);
		}
		else {
			int ans=min(M, lmin[z]);
			printf("%d\n", ans);
			last=ans;
		}
	}
}

