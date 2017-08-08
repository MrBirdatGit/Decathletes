#include <bits/stdc++.h>
using namespace std;
const int maxn=60500;

int n;
int last[maxn];
int pre[maxn];

struct node{
	int l,r;
	double M,add;
}T[maxn<<2];

void build(int u,int l,int r,double v){
	T[u].l=l;
	T[u].r=r;
	T[u].add=0;
	if(l==r){
		T[u].M=v*l;
		return;
	}
	int mid=(l+r)/2;
	build(2*u,l,mid,v);
	build(2*u+1,mid+1,r,v);
	T[u].M=min(T[2*u].M,T[2*u+1].M);
}

void pushdown(int u){
	T[2*u].M+=T[u].add;
	T[2*u].add+=T[u].add;
	T[2*u+1].M+=T[u].add;
	T[2*u+1].add+=T[u].add;
	T[u].add=0;
}

void update(int u,int l,int r){
	if(l<=T[u].l&&T[u].r<=r){
		T[u].add+=1;
		T[u].M+=1;
		return ;
	}
	pushdown(u);
	int mid=(T[u].l+T[u].r)/2;
	if(mid>=l)update(2*u,l,r);
	if(mid+1<=r)update(2*u+1,l,r);
	T[u].M=min(T[2*u].M,T[2*u+1].M);
}

double query(int u,int l,int r){
	if(l<=T[u].l&&T[u].r<=r){
		return T[u].M;
	}
	pushdown(u);
	int mid=(T[u].l+T[u].r)/2;
	double M=2.0*n;
	if(mid>=l)M=min(M,query(2*u,l,r));
	if(mid+1<=r)M=min(M,query(2*u+1,l,r));
	return M;
}


bool judge(double mid){
	build(1,1,n,mid);
	for(int i=1;i<=n;i++){
		update(1,pre[i]+1,i);
		if(query(1,1,i)<=mid*(i+1))return true;
	}
	return false;
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		memset(last,0,sizeof(last));
		for(int i=1;i<=n;i++){
			int a;
			scanf("%d",&a);
			pre[i]=last[a];
			last[a]=i;
		}
		double l=0,r=1;
		for(int i=1;i<=30;i++){
			double mid=(l+r)/2;
			if(judge(mid))r=mid;
			else l=mid;
		}
		printf("%.6f\n",l);
	}
}
