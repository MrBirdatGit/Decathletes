//学习了这里 http://www.cnblogs.com/autsky-jadek/p/7271450.html

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=305000;

int n,k;

struct edge{
    int to,next;
}e[2*maxn];
int head[maxn];
int cnt;

void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
}

void add(int u,int v){
    e[cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt++;
}

int lo[2*maxn];
int vs[2*maxn];
int dep[2*maxn];
int g[2*maxn][21];
int id[maxn];
int f[maxn];
ll dp[3][maxn];

void dfs(int u,int fa,int d,int &k){
    id[u]=k;
    vs[k]=u;
    dep[k++]=d;
    for(int i=head[u];~i;i=e[i].next){
        if(e[i].to!=fa){
            dfs(e[i].to,u,d+1,k);
            vs[k]=u;
            dep[k++]=d;
        }
    }
}

int query(int l,int r){
    int j=lo[r-l+1];
    int lid=g[l][j];
    int rid=g[r-(1<<j)+1][j];
    if(dep[lid]<=dep[rid])return lid;
    return rid;
}

int lca(int u,int v){
    return vs[query(min(id[u],id[v]),max(id[u],id[v]))];
}


int main(){
    for(int i=1;i<2*maxn;i++)lo[i]=31-__builtin_clz(i);
    while(~scanf("%d%d",&n,&k)){
        init();
        for(int i=1;i<=n;i++)scanf("%d",&f[i]);
        for(int i=1;i<n;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            add(u,v);
            add(v,u);
        }
        int K=0;
        dfs(1,-1,1,K);
        int len=2*n-1;
        for(int i=0;i<len;i++)g[i][0]=i;
        for(int j=1;1<<j<len;j++){
            for(int i=0;i+(1<<j)-1<len;i++){
                int l=dep[g[i][j-1]],r=dep[g[i+(1<<(j-1))][j-1]];
                if(l<=r){
                    g[i][j]=g[i][j-1];
                }
                else g[i][j]=g[i+(1<<(j-1))][j-1];
            }
        }
 		memset(dp,0,sizeof(dp));
 		for(int i=1;i<=n;i++){
 			for(int j=1;j<=min(k,i);j++){
 				ll now=1LL<<60;
 				if(j<=i-1)now=min(now,dp[(i+2)%3][j]);
 				now=min(now,dp[(i+2)%3][j-1]+dep[id[f[i]]]);
 				if(j<=i-1&&i>=2)now=min(now,dp[(i+1)%3][j-1]+dep[id[lca(f[i-1],f[i])]]);
 				dp[i%3][j]=now;
 			}
 		}      	
        printf("%lld\n",dp[n%3][k]);
    }    
}
