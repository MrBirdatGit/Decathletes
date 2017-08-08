#include <bits/stdc++.h>
using namespace std;
int n,q,c;
int x[105000],y[105000],s[105000];
int g[11][105][105];
int main(){
	scanf("%d%d%d",&n,&q,&c);
	for(int i=1;i<=n;i++)scanf("%d%d%d",&x[i],&y[i],&s[i]);
	for(int j=1;j<=n;j++)g[0][x[j]][y[j]]+=s[j];
	for(int i=1;i<=c;i++){
		for(int j=1;j<=n;j++){
			s[j]=(s[j]+1)%(c+1);
			g[i][x[j]][y[j]]+=s[j];
		}
	}
	for(int i=0;i<=c;i++){
		for(int j=1;j<=100;j++){
			for(int k=1;k<=100;k++)g[i][j][k]+=g[i][j][k-1];
		}
		for(int k=1;k<=100;k++){
			for(int j=1;j<=100;j++)g[i][j][k]+=g[i][j-1][k];
		}
	}
	while(q--){
		int t,xl,yl,xr,yr;
		scanf("%d%d%d%d%d",&t,&xl,&yl,&xr,&yr);
		int i=t%(c+1);
		printf("%d\n",g[i][xr][yr]-g[i][xr][yl-1]-g[i][xl-1][yr]+g[i][xl-1][yl-1]);
	}
}
