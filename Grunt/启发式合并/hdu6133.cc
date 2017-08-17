//启发式合并get
//NJU很牛逼啊
//这个sumofsum树状数组也很套路啊
//我TM好菜菜啊

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int a[105000];
int id[105000];
int b[105000];
ll num[105000];
ll sum[105000];
int lson[105000];
int rson[105000];
int n;

int cmp(int x, int y){
	if(a[x]==a[y])return x<y;
	return a[x]<a[y];
}

struct edge{
	int to, next;
}e[205000];

int head[105000];
int cnt;
int siz[105000];
ll ans[105000];
ll tmp;
ll tot;

void init(){
	tmp=0;
	memset(lson, -1, sizeof(lson));
	memset(rson, -1, sizeof(rson));
	memset(ans, 0, sizeof(ans));
	memset(num, 0, sizeof(num));
	memset(sum, 0, sizeof(sum));
	memset(head, -1, sizeof(head));
	cnt=0;
}

void add(int u, int v){
	e[cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt++;
}

void dfs(int u, int fa){
	siz[u]=1;
	for(int i=head[u];~i;i=e[i].next){
		if(e[i].to!=fa){
			dfs(e[i].to, u);
			siz[u]+=siz[e[i].to];
			if(rson[u]==-1)rson[u]=e[i].to;
			else {
				if(siz[e[i].to]>siz[rson[u]]){
					lson[u]=rson[u];
					rson[u]=e[i].to;
				}
				else {
					lson[u]=e[i].to;
				}
			}
		}
	}
}

int lowbit(int x){
	return x&(-x);
}

void update(ll f[], int pos, int val){
	while(pos<=tot){
		f[pos]+=val;
		pos+=lowbit(pos);
	}
}

ll query(ll f[], int pos){
	ll ans=0;
	while(pos){
		ans+=f[pos];
		pos-=lowbit(pos);
	}
	return ans;
}

void add(int u){
	tmp+=(query(num, tot)-query(num, b[u]))*a[u];
	tmp+=query(sum, b[u])+a[u];
	update(num, b[u], 1);
	update(sum, b[u], a[u]);
}

void del(int u){
	tmp-=(query(num, tot)-query(num, b[u]))*a[u];
	tmp-=query(sum, b[u]);
	update(num, b[u], -1);
	update(sum, b[u], -a[u]);
}

void addtree(int u){
	add(u);
	if(lson[u]!=-1)addtree(lson[u]);
	if(rson[u]!=-1)addtree(rson[u]);
}

void deltree(int u){
	del(u);
	if(lson[u]!=-1)deltree(lson[u]);
	if(rson[u]!=-1)deltree(rson[u]);
}

void dfs1(int u){
	if(lson[u]==-1){
		if(rson[u]==-1){
			add(u);
			ans[u]=tmp;
			return ;
		}
		dfs1(rson[u]);
		add(u);
		ans[u]=tmp;
		return;
	}
	dfs1(lson[u]);
	deltree(lson[u]);
	dfs1(rson[u]);
	addtree(lson[u]);
	add(u);
	ans[u]=tmp;
	return ;
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		init();
		scanf("%d", &n);
		for(int i=1;i<=n;i++){
			scanf("%d", &a[i]);
			id[i]=i;
		}
		sort(id+1, id+1+n, cmp);
		
		b[id[1]]=1;
		for(int i=2;i<=n;i++){
			if(a[id[i]]==a[id[i-1]])b[id[i]]=b[id[i-1]];
			else b[id[i]]=b[id[i-1]]+1;
		}
		tot=b[id[n]];

		for(int i=1;i<n;i++){
			int u, v;
			scanf("%d%d", &u, &v);
			add(u, v);
			add(v, u);
		}
		dfs(1, 0);
		dfs1(1);
		for(int i=1;i<=n;i++)printf("%lld ", ans[i]);
		printf("\n");
	}
}

