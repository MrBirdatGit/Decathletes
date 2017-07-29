#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m;
int a[105][105];
int nxt[105][105];
int val[105*105][105];
int l[105],r[105];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		ll sum=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",&a[i][j]);
		for(int v=0;v<n*m;v++)for(int i=1;i<=n;i++)val[v][i]=m+1;
		for(int i=1;i<=n;i++)for(int j=m;j>=1;j--){
			nxt[i][j]=val[a[i][j]][i];
			val[a[i][j]][i]=j;
		}
		for(int v=0;v<n*m;v++){
			for(int i=1;i<=n;i++){
				if(val[v][i]>m)continue;
				for(int u=1;u<=i;u++)l[u]=0,r[u]=val[v][u];
				for(int j=0,k=val[v][i];k<=m;j=k,k=nxt[i][k]){
					sum+=(k-j)*(m+1-k)*(n+1-i);
					int ml=j,mr=m+1;
					for(int u=i-1;u>=1;u--){
						while(r[u]<=k){l[u]=r[u];r[u]=nxt[u][r[u]];}
						ml=max(ml,l[u]),mr=min(mr,r[u]);
						sum+=(k-ml)*(mr-k)*(n+1-i);
					}	
				}
			}
		}
		printf("%.9f\n",sum*4.0/n/(n+1)/m/(m+1));
	}
}
