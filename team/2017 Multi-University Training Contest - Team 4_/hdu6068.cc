#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,q;
char s[50500];
char t[105];
int pre[105];
int suf[105];
int f[105][50500];
int g[105][50500];
ll ff[105][50500];
ll gg[105][50500];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		memset(ff,0,sizeof(ff));
		memset(gg,0,sizeof(gg));
		scanf("%d%d%d%s%s",&n,&m,&q,s+1,t+1);
		for(int i=1;i<=m;i++){
			pre[1]=0;
			for(int j=2;j<=i;j++){
				int k=pre[j-1];
				while(k&&t[k+1]!=t[j])k=pre[k];
				if(t[k+1]==t[j])k++;
				pre[j]=k;
			}
			for(int j=1,k=0;j<=n;j++){
				while(k&&t[k+1]!=s[j])k=pre[k];
				if(t[k+1]==s[j])k++;
				if(k==i){
					f[i][j]++;
					k=pre[k];
				}
				f[i][j]+=f[i][j-1];
				ff[i][j]=f[i][j]+ff[i][j-1];
			}
		}
		reverse(s+1,s+1+n);
		reverse(t+1,t+1+m);
		for(int i=1;i<=m;i++){
			suf[1]=0;
			for(int j=2;j<=i;j++){
				int k=suf[j-1];
				while(k&&t[k+1]!=t[j])k=suf[k];
				if(t[k+1]==t[j])k++;
				suf[j]=k;
			}
			for(int j=1,k=0;j<=n;j++){
				while(k&&t[k+1]!=s[j])k=suf[k];
				if(t[k+1]==s[j])k++;
				if(k==i){
					g[i][j]++;
					k=suf[k];
				}
				g[i][j]+=g[i][j-1];
				gg[i][j]=g[i][j]+gg[i][j-1];
			}
		}
		//cout<<f[1][1]<<endl;
		//cout<<f[3][3]<<' '<<g[2][2]<<endl;
		while(q--){
			int l,r;
			scanf("%d%d",&l,&r);
			ll ans=0;
			ans+=1LL*ff[m][l]*(n-r+1);
			//cout<<ans<<endl;
			ans+=1LL*gg[m][n-r+1]*l;
			//cout<<ans<<endl;
			for(int i=1;i<m;i++){
				ans+=1LL*f[i][l]*g[m-i][n-r+1];
				//printf("%d: f=%d g=%d ",i,f[i][l],g[m-i][n-r+1]);
				//cout<<ans<<endl;
			}
			printf("%lld\n",ans);
		}
	}
}
