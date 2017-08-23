/*
无源汇可行流 
虚拟一个源点s和一个汇点t，对每个点u,设D(u)=∑bin−∑bout,若D(u)>0，从s连一条容量为D(u)的流到u,否则连一条容量为-D(u)的流到t。
建完图，跑一遍最大流，如果s->t满流则说明有可行流，一条可行流的边上流量为新图中流的流量+它的下界。
有源汇可行流 
在原图中连一条t到s，容量为INF的流。虚拟出一个超级源点ss和超级汇点tt，按上个问题的方式建图。
有源汇最大流
所以去掉ss和tt，在上一次最大流跑完后的残留网络上再跑一次最大流，结果就是所要的答案，这是因为残留网络上t->s的流量被退回来，相当于是加上了可行流的流量。
有源汇最小流 
增设ss和tt,但不连t->s的流，先跑一次最大流，这样可以去除上述的冗余流量(我的理解)。再连一条t->s的流，跑一次ss->tt的最大流，这时候s->t的流量(也是t->s的流的流量)即为最小流。
*/
//去掉了flow了cap的区分
const int maxn;
const int maxm;
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
int MCMF(int s,int t){
    int flow = 0;
    int cost = 0;
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

    return cost;
}