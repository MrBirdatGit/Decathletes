/*
晚上一小时的题
需要注意求无向图边双连通分量的方式是标记边而不是标记点
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 200100;
const int maxm = 1000100*4;
int head[maxn],tot;
struct edge{
    int to,next,vis;
}e[maxm];
void addedge(int u,int v){
    e[tot].to = v;
    e[tot].next = head[u];
    e[tot].vis = 0;
    head[u] = tot++;
}
int dfn[maxn],low[maxn],stk[maxn],belong[maxn],top,ins[maxn],clk,scc,num[maxn];
void init(){
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(ins,0,sizeof(ins));
    tot = top = clk = scc = 0;
}
void Tarjan(int u){
    int v;
    dfn[u] = low[u] = ++clk;
    stk[top++] = u;
    ins[u] = 1;
    for(int i = head[u];i!=-1;i=e[i].next){
        int v = e[i].to;
        if(e[i].vis) continue;
        e[i].vis = e[i^1].vis = 1;
        if(!dfn[v]){
            Tarjan(v);
            low[u] = min(low[u],low[v]);    
        }else if(ins[v]){
            low[u] = min(low[u],dfn[v]);
        }
    }
    if(low[u] == dfn[u]){
        scc++;
        do{
            v = stk[--top];
            ins[v] = 0;
            belong[v] = scc;
            num[scc]++;
        }while(u != v);
    }
}
vector<int>G[maxn];
bool vis[maxn];
int ml;
int z;
void dfs(int s,int d){
    vis[s] = 1;
    if(d > ml){
        ml = d;
        z = s;
    }
    for(int i = 0;i<G[s].size();i++){
        if(!vis[G[s][i]]){
            dfs(G[s][i],d+1);
        }
    }
}
int main(){
	int n,m,u,v;
	while(~scanf("%d%d",&n,&m)){
        if(n == 0)break;
		init();
		for(int i = 0;i<m;i++){
			scanf("%d%d",&u,&v);
			addedge(u,v);
            addedge(v,u);
        }
		for(int i = 1;i<=n;i++){
			if(!dfn[i])
                Tarjan(i);
            G[i].clear();
        }
        // for(int i = 1;i<=n;i++){
        //     cout<<' '<<belong[i];
        // }cout<<endl;
        // cout<<scc<<endl;
        for(int i = 1;i<=n;i++){
            for(int j = head[i];j!=-1;j=e[j].next){
                int v = e[j].to;
                if(belong[i] != belong[v]){
                    G[belong[i]].push_back(belong[v]);
                    G[belong[v]].push_back(belong[i]);
                }
            }
        }
        ml = 0;
        memset(vis,0,sizeof(vis));
        dfs(1,0);
        memset(vis,0,sizeof(vis));
        dfs(z,0);
        printf("%d\n",scc - ml -1);
	}
    
}