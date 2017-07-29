#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;

int n;
int a[105000];
int M;

bool vis[105000];
int prime[105000];
int tot;

void init(){
	tot=0;
	memset(vis,false,sizeof(vis));
	for(int i=2;i<=100000;i++){
		if(!vis[i]){
			prime[++tot]=i;
			for(int j=2;j*i<=100000;j++)vis[j*i]=true;		
		}		
	}
}

int p[10];
int cnt;

void fj(int num){
	cnt=0;
	for(int i=1;i<=tot&&prime[i]*prime[i]<=num;i++){
		if(num%prime[i]==0){
			p[++cnt]=prime[i];
			while(num%prime[i]==0)num/=prime[i];	
		}
	}
}

ll ans=0;

void gao(){
	ans=0;
	for(int i=0;i<1<<cnt;i++){
		int mul=1;
		int tim=0;
		for(int j=1;j<=cnt;j++){
			if(i&(1<<(j-1))){
				mul*=p[j];
				tim++;
			}
		}
		ll tmp=1;
		for(int j=1;j<=n;j++){
			tmp=tmp*(a[j]/mul)%mod;
		}
		if(tim%2==0)ans=(ans-tmp+mod)%mod;
		else ans=(ans+tmp)%mod;
	}
}

int main(){
	init();
	int T;
	scanf("%d",&T);
	for(int tt=1;tt<=T;tt++){
		M=105000;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);	
			M=min(M,a[i]);			
		}
		fj(M);
		cout<<cnt<<endl;
		gao();
		printf("Case #%d: %lld\n", tt, ans);
	}
}

