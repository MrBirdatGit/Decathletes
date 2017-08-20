#include <bits/stdc++.h>
using namespace std;
const int maxn=200005;

struct edge{
	int to, next;
}e[maxn<<1];
int head[maxn];
int cnt;

void init(){
	cnt=0;
	memset(head, -1, sizeof(head));
}

void add(int u, int v){
	e[cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt++;
}

int n, siz;

int a[maxn];
int vs[maxn<<1];
int l[maxn], r[maxn];

void dfs(int u, int fa, int &k){
	l[u]=k;
	vs[k++]=u;
	for(int i=head[u];~i;i=e[i].next){
		if(e[i].to!=fa){
			dfs(e[i].to, u, k);
			vs[k++]=u;
		}
	}
	r[u]=k-1;
}

struct query{
	int l, r, id;
}rec[maxn];

bool cmp(query a, query b){
	if(a.l/siz==b.l/siz)return a.r<b.r;
	return a.l<b.l;
}

int used[maxn];
int ans[maxn];
int tmp, le, ri;

void update(int pos, int add){
	int num=a[vs[pos]];
	if(add==1){
		if(used[num]==0)tmp++;
		used[num]++;
	}
	else {
		used[num]--;
		if(used[num]==0)tmp--;
	}
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		siz=sqrt(2*n);
		init();
		for(int i=1;i<=n;i++){
			scanf("%d", &a[i]);
		}
		for(int i=1;i<n;i++){
			int u, v;
			scanf("%d%d", &u, &v);
			add(u, v);
			add(v, u);
		}
		int k=0;
		dfs(1, 0, k);
	//	for(int i=1;i<=n;i++)printf("%d ", l[i]);
	//	printf("\n");
	//	for(int i=1;i<=n;i++)printf("%d ", r[i]);
	//	printf("\n");
		int q;
		scanf("%d", &q);
		for(int i=1;i<=q;i++){
			int u;
			scanf("%d", &u);
			rec[i].l=l[u], rec[i].r=r[u];
			rec[i].id=i;
			//cout<<l[u]<<' '<<r[u]<<endl;
		}
		sort(rec+1, rec+1+n, cmp);
		memset(used, 0, sizeof(used));
		tmp=0, le=1, ri=0;
		for(int i=1;i<=q;i++){
			while(ri<rec[i].r){
				update(ri+1, 1);
				ri++;
			}
			while(le>rec[i].l){
				update(le-1, 1);
				le--;
			}
			while(ri>rec[i].r){
				update(ri, -1);
				ri--;
			}
			while(le<rec[i].l){
				update(le, -1);
				le++;
			}
			ans[rec[i].id]=tmp;
		}
		for(int i=1;i<=q;i++)printf("%d\n", ans[i]);
	}
	//printf("Time used = %.2f\n", (double)clock()/CLOCKS_PER_SEC);
}

