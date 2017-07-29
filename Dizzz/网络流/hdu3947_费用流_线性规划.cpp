/*
对每个点设P[a] = X[1] + X[2] + ... + x[i]  = W[a] + Y[a]  i为可用药品数
两两相减
X[u] + X[v] + .. -X[w] - W[a] - Y[a] + W[b] + Y[b] = 0
把变量当作流量
*/

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
const int maxn = 410;
const int maxm = maxn * maxn;
const int inf = 1<<30;
struct edge{
    int to,next,f,cost;
}e[maxm];
int head[maxn],tot;
int pre[maxn],dis[maxn];
bool vis[maxn];
void init(int t){
    tot = 1;
    // memset(head,0,sizeof(head));
    for(int i = 0;i<=t;i++)
        head[i] = 0;
}
inline void addedge(int u,int v,int cap,int cost){
    e[++tot].to = v;
    e[tot].f = cap;
    e[tot].cost = cost;
    e[tot].next = head[u];
    head[u] = tot;
    e[++tot].to = u;
    e[tot].f = 0;
    e[tot].cost = -cost;
    e[tot].next = head[v];
    head[v] = tot;
}
int spfa(int s,int t){
    queue<int>q;
    for(int i = 0;i<=t;i++){
        dis[i] = inf;
        vis[i] = 0;
        pre[i] = -1;
    }
    dis[s] = 0;
    vis[s] = 1;
    q.push(s);
    while(!q.empty()){
        int u = q.front();q.pop();
        vis[u] = 0;
        for(int i = head[u];i;i = e[i].next){
            int v = e[i].to;
            if(e[i].f && dis[v] > dis[u] + e[i].cost){
                dis[v] = dis[u] + e[i].cost;
                pre[v] = i;
                if(!vis[v]){
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return pre[t] != -1;
}
int MCMF(int s,int t,int &cost){
    int flow = 0;
    cost = 0;
    while(spfa(s,t)){
        int Min = inf;
        for(int i = pre[t];i!=-1;i=pre[e[i^1].to]){
            if(Min > e[i].f)
                Min = e[i].f;
        }
        for(int i = pre[t];i!=-1;i=pre[e[i^1].to]){
            e[i].f -= Min;
            e[i^1].f += Min;
            cost += e[i].cost * Min;
        }
        flow += Min;
    }

    return flow;
}
int main(){
    int T,n,m,u,v,w,l;
    scanf("%d",&T);
    for(int cs = 1;cs<=T;cs++){
        scanf("%d",&n);
        int s = 0,t = n+1;
        init(t);
        int sum = 0;
        for(int i = 1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            addedge(u,t,w,0);
            addedge(s,v,w,0);
            addedge(u,v,inf,0);
            sum += w;
        }
        scanf("%d",&m);
        while(m--){
            scanf("%d%d%d%d",&u,&v,&l,&w);
            addedge(v,u,l,w);
        }
        int cost;
        printf("Case #%d: ",cs);
        if(MCMF(s,t,cost) != sum) printf("-1\n");
        else printf("%d\n",cost);
    }
    
}