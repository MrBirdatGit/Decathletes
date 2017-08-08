#include <bits/stdc++.h>
using namespace std;
int T,n;
int prime[105000];
bool vis[105000];
int tot;

void init(){
	tot=0;
	for(int i=2;i<=100000;i++){
		if(!vis[i]){
			prime[++tot]=i;
			for(int j=2;j*i<=100000;j++)vis[i*j]=true;
		}
	}
}

int a[105000];
int cnt[105000];

int main(){
	init();
	scanf("%d",&T);
	for(int tt=1;tt<=T;tt++){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		bool ok=false;
		for(int i=1;prime[i]<=n;i++){
			memset(cnt,0,sizeof(cnt));
			for(int j=1;j<=n;j++)cnt[a[j]%prime[i]]++;
			for(int j=0;j<prime[i];j++){
				if(cnt[j]*2>=n){
					printf("%d %d\n",prime[i],j);
					ok=true;
					break;
				}
			}
			if(ok)break;
		}
	}
}
