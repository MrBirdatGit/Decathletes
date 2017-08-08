#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m;
vector<int>g[105000];
char s[105000];
ll ans[105000];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		g[i].push_back(0);
		for(int j=1;j<=m;j++){
			if(s[j]=='.'){ans[1]++;g[i].push_back(0);}
			else g[i].push_back(1);
		}
	}
	for(int i=1;i<=n;i++){
		int tmp=0;
		for(int j=1;j<=m+1;j++){
			if(j==m+1||g[i][j]==1){
				for(int k=2;k<=tmp;k++)ans[k]+=tmp-k+1;
				tmp=0;
			}
			else {
				tmp++;
			}
		}
	}
	for(int j=1;j<=m;j++){
		int tmp=0;
		for(int i=1;i<=n+1;i++){
			if(i==n+1||g[i][j]==1){
				for(int k=2;k<=tmp;k++)ans[k]+=tmp-k+1;
				tmp=0;
			}
			else {
				tmp++;
			}
		}
	}
	int tot=max(n,m);
	for(int i=1;i<=tot;i++)printf("%lld%c",ans[i],i==tot?'\n':' ');
}
