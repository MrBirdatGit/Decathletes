#include<bits/stdc++.h>
using namespace std;
const int maxn = 50010;
int n,x,y;
vector<int>G[maxn];
int val[maxn];
int ori[maxn];
int p[maxn];
int dp[maxn][2];
void dfs(int u,int st){
    st ^= p[u];
    int now = st ^ ori[u];
    dp[u][0] = now?-val[u]:val[u];
    dp[u][1] = now?val[u]:-val[u];
    for(int i = 0;i<G[u].size();i++){
        int v = G[u][i];
        dfs(v,st);
        dp[u][0] += max(dp[v][0],dp[v][1] - (p[v]?y:x));
        dp[u][1] += max(dp[v][1],dp[v][0] - (p[v]?y:x));
    }
}
int main(){
    while(~scanf("%d%d%d",&n,&x,&y)){
        int fa;
        for(int i = 0;i<=n;i++) G[i].clear();
        memset(dp,0,sizeof(dp));
        for(int i = 1;i<=n;i++){
            scanf("%d%d%d%d",&val[i],&fa,&p[i],&ori[i]);
            G[fa].push_back(i);
        }
        val[0]  = ori[0] = 0;
        dfs(0,0);
        if(dp[0][0] < 0)
            printf("HAHAHAOMG\n");
        else    
            printf("%d\n",dp[0][0]);
    }
}