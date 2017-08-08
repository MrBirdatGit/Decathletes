//题意是求一个二维矩阵的所有子矩阵的价值和
//每个子矩阵的价值是不同的元素个数
//参考(chao)了poursoul大爷的写法
//大致是考虑每个数作为矩形在该数上主值的出现次数
//注意写法
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
