#include <bits/stdc++.h>
using namespace std;
double eps=1e-8;
int x[1050];
int y[1050];
int w[1050];
struct edge{
	int l, r;
	double len, v;
}rec[1005000];
bool cmp(edge a, edge b){
	return a.len<b.len;
}
int tot;
int n;

int fa[1050];
int p[1050];
int rp[1050];
double rl[1050];

int getfa(int u){
	if(u==fa[u])return u;
	p[fa[u]]=max(p[fa[u]], p[u]);
	return fa[u]=getfa(fa[u]);
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i=1;i<=n;i++){fa[i]=i;}
		for(int i=1;i<=n;i++){
			scanf("%d%d%d", &x[i], &y[i], &w[i]);
			p[i]=w[i];
		}
		tot=0;
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				++tot;
				rec[tot].len=sqrt(1.0*(x[i]-x[j])*(x[i]-x[j])+1.0*(y[i]-y[j])*(y[i]-y[j]));
				rec[tot].v=1.0*(w[i]+w[j]);
				rec[tot].l=i, rec[tot].r=j;
			}
		}
		sort(rec+1, rec+1+tot, cmp);
		int j=1;
		double sum=0;
		for(int i=1;i<=n-1;i++){
			while(1){
				int l=rec[j].l, r=rec[j].r;
				if(getfa(l)!=getfa(r))break;
				j++;
			}
			int l=rec[j].l, r=rec[j].r;
			l=getfa(l), r=getfa(r);
			rp[i]=p[l]+p[r];
			rl[i]=rec[j].len;
			p[r]=max(p[l], p[r]);
			fa[l]=r;
			sum+=rec[j].len;
			j++;
		}
		double M=0;
		for(int i=1;i<n;i++){
			M=max(M, 1.0*(rp[i])/(sum-rl[i]));
		}
		printf("%.2f\n", M);
	}
}

