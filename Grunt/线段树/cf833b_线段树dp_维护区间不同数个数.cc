#include <bits/stdc++.h>
using namespace std;
const int maxn=35005;
int n,k;
int last[maxn];
int pre[maxn];
int dp[51][maxn];
struct node{
	int l,r;
	int add;
	int M;
}T[4*maxn];

void build(int k,int u,int l,int r){
	T[u].l=l;
	T[u].r=r;
	T[u].add=0;
	if(l==r){
		T[u].M=dp[k][l];
		return ;
	}
	int mid=l+r>>1;
	build(k,2*u,l,mid);
	build(k,2*u+1,mid+1,r);
	T[u].M=max(T[2*u].M,T[2*u+1].M);
}

void pushdown(int u){
	if(T[u].add==0)return ;
	T[2*u].add+=T[u].add;
	T[2*u].M+=T[u].add;
	T[2*u+1].add+=T[u].add;
	T[2*u+1].M+=T[u].add;
	T[u].add=0;
}

void update(int u,int l,int r){
	if(T[u].l>=l&&T[u].r<=r){
		T[u].add++;
		T[u].M++;
		return ;
	}
	pushdown(u);
	int mid=T[u].l+T[u].r>>1;
	if(mid>=l)update(2*u,l,r);
	if(mid+1<=r)update(2*u+1,l,r);
	T[u].M=max(T[2*u].M,T[2*u+1].M);
}

int query(int u,int l,int r){
	int M=0;
	if(T[u].l>=l&&T[u].r<=r){
		return T[u].M;
	}
	pushdown(u);
	int mid=T[u].l+T[u].r>>1;
	if(mid>=l)M=max(M,query(2*u,l,r));
	if(mid+1<=r)M=max(M,query(2*u+1,l,r));
	return M;
}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		int a;
		scanf("%d",&a);
		dp[1][i]=dp[1][i-1]+!last[a];
		pre[i]=last[a];
		last[a]=i;
	}
	for(int i=2;i<=k;i++){
		build(i-1,1,0,n);
		for(int j=1;j<=n;j++){
			update(1,pre[j],j-1);
			dp[i][j]=query(1,0,j-1);
		}
	}
	printf("%d\n",dp[k][n]);
}
