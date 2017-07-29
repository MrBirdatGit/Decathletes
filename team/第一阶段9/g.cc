#include<bits/stdc++.h>
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
#define ls rt<<1
#define rs rt<<1|1
#define mid int m = (l+r)>>1
using namespace std;
const int maxn =  200010;
int N, M, P;
struct node{
	int add, minn, maxn;
}nd[maxn<<2];
void build(int l, int r, int rt){
	nd[rt].minn = nd[rt].maxn = nd[rt].add = 0;
	if(l == r) return;
	mid;
	build(lson);
	build(rson);
}
void pushup(int rt){
	nd[rt].maxn = max(nd[ls].maxn, nd[rs].maxn);
	nd[rt].minn = min(nd[ls].minn, nd[rs].minn);
}
void pushdown(int rt){
	if(nd[rt].add){
		nd[ls].maxn += nd[rt].add;
		nd[rs].maxn += nd[rt].add;
		nd[ls].minn += nd[rt].add;
		nd[rs].minn += nd[rt].add;
		nd[rt].add = 0;
	}
}
void update(int L, int R, int l, int r, int rt, int x){
	if(L <= l && r <= R){
		if(nd[rt].maxn < P){
			nd[rt].maxn += x;
			nd[rt].minn += x;
			nd[rt].add += x;
			return;
		}
		else if(nd[rt].minn >= P){
			nd[rt].add += 2*x;
			nd[rt].minn += 2*x;
			nd[rt].maxn += 2*x;
			return;
		}
	}
	mid;
	pushdown(rt);
	if(L <= m) update(L, R, lson, x);
	if(m < R) update(L, R, rson, x);
	pushup(rt);
}
void query(int L, int R, int l, int r, int rt){
	if(l == r){
		printf("%d%c", nd[rt].maxn,l==N?'\n':' ');
		return;
	}
	mid;
	pushdown(rt);
	query(L, R, lson);
	query(L, R, rson);
}
int main(){
	while(~scanf("%d%d%d", &N, &M, &P)){
		build(1, N, 1);
		int a, b, c;
		for(int i = 0;i<M;i++){
			scanf("%d%d%d", &a, &b, &c);
			update(a, b, 1, N, 1, c);
		}
		query(1, N, 1, N, 1);
	}
}

