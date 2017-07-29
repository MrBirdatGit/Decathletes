#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m;
int g[105][105];
int tmp[105][105];
int l[105][105];
int r[105][105];
struct node {
	int x,y;
};
vector<node>v[10500];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=0;i<n*m;i++)v[i].clear();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%d",&g[i][j]);
				v[g[i][j]].push_back((node){i,j});
			}
		}
		ll ans=0;
		for(int i=0;i<n*m;i++){
			int siz=v[i].size();
			if(siz==0)continue;
			if(siz<=13){
				for(int st=1;st<1<<siz;st++){
					int xs=n+1,xl=0,ys=m+1,yl=0;
					int cnt=0;
					for(int j=0;j<siz;j++){
						if((st>>j)&1){
							cnt++;
							xs=min(xs,v[i][j].x);
							xl=max(xl,v[i][j].x);
							ys=min(ys,v[i][j].y);
							yl=max(yl,v[i][j].y);
						}
					}
					ll add=1LL*xs*ys*(n-xl+1)*(m-yl+1);
					if(cnt&1)ans+=add;
					else ans-=add;
				}
			}
			else {
				for(int j=1;j<=n;j++){
					for(int k=1;k<=m;k++){
						if(g[j][k]==i)tmp[j][k]=0;
						else tmp[j][k]=1;
					}
				}
				for(int j=1;j<=n;j++){
					for(int k=1;k<=m;k++){
						if(k!=1&&tmp[j][k-1]!=0)l[j][k]=l[j][k-1];
						else l[j][k]=k;
					}
				}
				for(int j=1;j<=n;j++){
					for(int k=m;k>=1;k--){
						if(k!=m&&tmp[j][k+1]!=0)r[j][k]=r[j][k+1];
						else r[j][k]=k;
					}
				}
				ll opp=0;
				
				for(int k=1;k<=m;k++){
					int lp=k,rp=m+1;
					int len=0;
					for(int j=1;j<=n;j++){
						if(tmp[j][k]==0){
							lp=l[j][k];
							rp=m+1;
							len=0;
						}
						else {
							len++;
							lp=max(lp,l[j][k]);
							rp=min(rp,r[j][k]);
							opp+=len*(rp-lp+1);
						}
					}
				}
				ans+=1LL*n*(n+1)*m*(m+1)/4-opp;
			}
		}
		ll tot=1LL*n*(n+1)*m*(m+1)/4;
		double rt=1.0*ans/tot;
		printf("%.9f\n",rt);
	}
}
