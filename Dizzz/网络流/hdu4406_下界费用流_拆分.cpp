#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
//去掉了flow了cap的区分
const int maxn = 210;
const int maxm = maxn * maxn;
const int inf = 1<<30;
const int M = 1e5;
struct edge{
    int to,next,f;
    double cost;
}e[maxm];
int head[maxn],tot;
int pre[maxn];
double dis[maxn];
bool vis[maxn];
void init(int t){
    tot = 1;
    // memset(head,0,sizeof(head));
    for(int i = 0;i<=t;i++)
        head[i] = 0;
}
inline void addedge(int u,int v,int cap,double cost){
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
        dis[i] = M * 1.0;
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

double MCMF(int s,int t){
    int flow = 0;
    double cost = 0;
    while(spfa(s,t)){
        int Min = inf;
        for(int i = pre[t];i!=-1;i=pre[e[i^1].to]){
            if(Min > e[i].f)
                Min = e[i].f;
        }
        for(int i = pre[t];i!=-1;i=pre[e[i^1].to]){
            e[i].f -= Min;
            e[i^1].f += Min;
            cost += 1.0 * e[i].cost * Min;
        }
        flow += Min;
    }

    return cost;
}
double cal(int x,int c){
    return (4.0 - 3.0 * (100-x) * (100-x)/1600) * c;
}
int crd[100],src[100];
int main(){
    // freopen("a.in","r",stdin);
    int n,k,m,tmp;
    while(~scanf("%d%d%d",&n,&k,&m)){
        int s = 0,t = n + m + 1;
        init(t);
        if(n + k + m == 0) break;
        int sum = 0;
        for(int i = 1;i<=m;i++){
            scanf("%d",&crd[i]);
            sum += crd[i];
        }
        for(int i = 1;i<=m;i++){
            scanf("%d",&src[i]);
            if(src[i] < 60){
                addedge(s,i,60-src[i],-1.0*M);
                for(int j = 61;j<=100;j++){
                    addedge(s,i,1,cal(j-1,crd[i])-cal(j,crd[i]));
                }
            }
            else{
                for(int j = src[i] + 1;j<=100;j++){
                    addedge(s,i,1,cal(j-1,crd[i])-cal(j,crd[i]));
                }
            }
        }
        for(int i = 1;i<=n;i++){
            addedge(i+m,t,k,0);
            for(int j = 1;j<=m;j++){
                scanf("%d",&tmp);
                if(tmp) addedge(j,i+m,k,0);
            }
        }
        MCMF(s,t);
        for(int i = head[s];i;i=e[i].next){
            src[e[i].to] += e[i^1].f;
        }
        double ans = 0;
        for(int i = 1;i<=m;i++){
            if(src[i] < 60){
                ans = 0;
                break;
            }
            ans += cal(src[i],crd[i]);
        }
        printf("%.6f\n",ans/sum);
    }
}