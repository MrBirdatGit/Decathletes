const int maxn = 100010;
const int maxm = 1000010;
const int inf = 0x3f3f3f3f;
struct edge{
    int to,next,cap,flow,cost;
}e[maxm];
int head[maxn],tot;
int pre[maxn],dis[maxn];
bool vis[maxn];
void init(){
    tot = 1;
    memset(head,0,sizeof(head));
}
void addedge(int u,int v,int cap,int cost){
    e[++tot].to = v;
    e[tot].cap = cap;
    e[tot].flow = 0;
    e[tot].cost = cost;
    e[tot].next = head[u];
    head[u] = tot;
    e[++tot].to = u;
    e[tot].cap = 0;
    e[tot].flow = 0;
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
            if(e[i].cap > e[i].flow && dis[v] > dis[u] + e[i].cost){
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
            if(Min > e[i].cap - e[i].flow)
                Min = e[i].cap - e[i].flow;
        }
        for(int i = pre[t];i!=-1;i=pre[e[i^1].to]){
            e[i].flow += Min;
            e[i^1].flow -= Min;
            cost += e[i].cost * Min;
        }
        flow += Min;
    }
    return flow;
}