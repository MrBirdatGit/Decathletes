#include <bits/stdc++.h>
using namespace std;
long long n, m;

long long degree[1050];
long long ans[1050];

struct edge{
	long long to, next, w;
}e[10500];
long long head[1050];
long long cnt;

void init(){
	memset(ans, 0, sizeof(ans));
	memset(degree, 0, sizeof(degree));
	memset(head, -1, sizeof(head));
	cnt=0;
}

void add(long long u, long long v, long long w){
	degree[v]++;
	e[cnt].to=v;
	e[cnt].w=w;
	e[cnt].next=head[u];
	head[u]=cnt++;
}

queue<long long>q;

int main()
{
	while(~scanf("%lld%lld", &n, &m)){
		init();
		for(long long i=1;i<=m;i++){
			long long u, v, w;
			scanf("%lld%lld%lld", &u, &v, &w);
			u++;v++;
			add(u, v, w);
		}
		while(!q.empty())q.pop();
		for(long long i=1;i<=n;i++){
			if(!degree[i]){
				q.push(i);
			}
		}
		while(!q.empty()){
			long long tmp=q.front();
			q.pop();
			for(long long i=head[tmp];~i;i=e[i].next){
				long long v=e[i].to;
				degree[v]--;
				ans[v]=max(ans[v], ans[tmp]+e[i].w);
				if(!degree[v])q.push(v);
			}
		}
		long long tans=0;
		for(long long i=1;i<=n;i++)tans=max(tans, ans[i]);
		printf("%lld\n", tans+1);
	}
}

