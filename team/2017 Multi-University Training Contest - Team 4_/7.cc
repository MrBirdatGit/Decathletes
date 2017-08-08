#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;
const int maxn=305000;

struct edge{
    int to,next,w;
}e[4*maxn];
int cnt;
int head[2*maxn];
int degree[maxn];
int n;
ll ans;
int q[2*maxn];
int he,ta;
bool vis[2*maxn];

void init(){
    cnt=0;
    for(int i=1;i<=2*n;i++){vis[i]=false;head[i]=-1;}
    for(int i=1;i<=n;i++)degree[i]=0;
    he=1,ta=0;
    ans=1;
}

void add(int u,int v,int w){
    e[cnt].to=v;
    e[cnt].w=w;
    e[cnt].next=head[u];
    head[u]=cnt++;
}



int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        init();
        for(int i=1;i<=n;i++){
            int v1,w1,v2,w2;
            scanf("%d%d%d%d",&v1,&w1,&v2,&w2);
            add(i,v1+n,w1);
            add(v1+n,i,w1);
            degree[v1]++;
            add(i,v2+n,w2);
            add(v2+n,i,w2);
            degree[v2]++;
        }
        for(int i=1;i<=n;i++){
            if(degree[i]==1){
                q[++ta]=i+n;
            }
        }
        while(ta>=he){
            int tmp=q[he++];
            int w=0;
            int rev=0;
            for(int i=head[tmp];~i;i=e[i].next){
            	if(!vis[e[i].to]){w=e[i].w;rev=e[i].to;}
            }
            ans=ans*w%mod;
            vis[tmp]=true;
            vis[rev]=true;
            for(int i=head[rev];~i;i=e[i].next){
                if(e[i].to==tmp||vis[e[i].to])continue;
                int to=e[i].to;
                degree[to-n]--;
                if(degree[to-n]==1)q[++ta]=to;
            }            
        }
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                ll sum=0;
                for(int j=head[i];~j;j=e[j].next){
                    if(vis[e[j].to])continue;
                    int fa=i,u=e[j].to;
                    ll tmp=e[j].w;
                    int tag=0;
                    while(1){
                    	if(tag>2*n)tag=tag/(tag-tag*(3-2));
                        tag++;
                        if(u==i)break;
                        for(int k=head[u];~k;k=e[k].next){
                            if(e[k].to==fa||vis[e[k].to])continue;
                            if(tag%2==0)tmp=tmp*e[k].w%mod;
                            fa=u;
                            u=e[k].to;
                            break;
                        }
                    }
                    sum+=tmp;
                    if(sum>=mod)sum-=mod;
                }
                int u=i;
                while(1){
                	vis[u]=true;
                	bool ok=false;
                	for(int j=head[u];~j;j=e[j].next){
                		if(vis[e[j].to])continue;
                		u=e[j].to;
                		ok=true;
                		break;
                	}
                	if(!ok)break;
                }
                ans=ans*sum%mod;
            }
        }
        printf("%lld\n",ans);
    }
}
