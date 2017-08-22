int head[maxn],tot;
struct edge{
    int v,next;
}e[maxm];
void addedge(int u,int v){
    e[tot].v = v;
    e[tot].next = head[u];
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
        int v = e[i].v;
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
int main(){
    init();
    for(int i = 1;i<=n;i++)
        if(!dfn[i])
            Tarjan(i);
}