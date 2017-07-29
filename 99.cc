#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;

ll power(ll n,ll p){
	ll ans=1;
	ll base=n;
	while(p){
		if(p&1){
			ans=ans*base%mod;
		}
		p>>=1;
		base=base*base%mod;
	}
	return ans;
}

int pre[105000];
int mu[105000];
bool vis[105000];
int prime[105000];
int cnt;
int n;
int M;
int Ma;

    void Init()  
    {  
	int N=100000;
        memset(vis,0,sizeof(vis));  
        mu[1] = 1;  
        cnt = 0;  
        for(int i=2; i<N; i++)  
        {  
            if(!vis[i])  
            {  
                prime[cnt++] = i;  
                mu[i] = -1;  
            }  
            for(int j=0; j<cnt&&i*prime[j]<N; j++)  
            {  
                vis[i*prime[j]] = 1;  
                if(i%prime[j]) mu[i*prime[j]] = -mu[i];  
                else  
                {  
                    mu[i*prime[j]] = 0;  
                    break;  
                }  
            }  
        }  
    }  

int main(){
	Init();
	//for(int i=1;i<=10;i++)printf("%d %d\n",i,mu[i]);
	int T;
	scanf("%d",&T);
	for(int tt=1;tt<=T;tt++){
		M=100000;
		Ma=0;
		memset(pre,0,sizeof(pre));
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			int x;
			scanf("%d",&x);
			pre[x]++;
			M=min(M,x);
			Ma=max(Ma,x);		
		}
		for(int i=1;i<=100000;i++)pre[i]+=pre[i-1];
		ll ans=0;
		//printf("%d %d\n",M,Ma);		
		for(int i=2;i<=M;i++){
			if(mu[i]==0)continue;			
			ll tmp=1;
			for(int j=1;j*i<=Ma;j++){
				int r=min(Ma,i*(j+1)-1);
				int l=i*j;
				tmp=tmp*power(j,pre[r]-pre[l-1])%mod;	
			}
			ans=(ans-mu[i]*tmp);
			ans%=mod;
			if(ans<0)ans+=mod;
		}
		printf("Case #%d: %lld\n",tt,ans);
	}
}
