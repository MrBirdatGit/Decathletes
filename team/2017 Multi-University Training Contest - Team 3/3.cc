#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,k;
int a[500500];
int pre[500500][2];
int suf[500500][2];
int l[105];
int r[105];
int lc,rc;
int main(){
	int T;
	scanf("%d",&T);
	while(T--){	
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)pre[i][0]=suf[i][0]=i;
		for(int j=1;j<=1;j++){
			for(int i=1;i<=n;i++){
				if(pre[i][j-1]==0)pre[i][j]=0;
				else {
					int last=pre[i][j-1]-1;
					while(last&&a[last]<a[i]){
						last=pre[last][1];
					}
					pre[i][j]=last;
				}
			}
		}
		for(int j=1;j<=1;j++){
			for(int i=n;i>=1;i--){
				if(suf[i][j-1]==n+1)suf[i][j]=n+1;
				else {
					int last=suf[i][j-1]+1;
					while(last<=n&&a[last]<a[i]){
						last=suf[last][1];
					}
					suf[i][j]=last;
				}
			}
		}
		
		ll ans=0;
		//for(int i=1;i<=n;i++)printf("%d %d\n",i,pre[i][1]);
		//for(int i=1;i<=n;i++)printf("%d %d\n",i,suf[i][1]);
		for(int i=1;i<=n;i++){
			int cnt=0;
			l[0]=i;
			r[0]=i;
			lc=0,rc=0;
			int now=i;
			while(now){
				now--;
				while(now&&a[now]<a[i]){
					now=pre[now][1];
				}
				l[++lc]=now;
				if(lc>=k+1)break;
			}
			now=i;
			while(now<=n){
				now++;
				while(now<=n&&a[now]<a[i]){
					now=suf[now][1];
				}
				r[++rc]=now;
				if(rc>=k+1)break;
			}
			ll sum=0;
			for(int u=0;u<=k-1;u++){
				int v=k-1-u;
				if(u>lc-1||v>rc-1)continue;
				sum+=1LL*(l[u]-l[u+1])*(r[v+1]-r[v]);
			}
			ans+=sum*a[i];
		}
		printf("%lld\n",ans);
	}
}
