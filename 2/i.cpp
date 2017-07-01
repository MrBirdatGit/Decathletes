#include <bits/stdc++.h>
using namespace std;
vector<int>g[105000];
int n,m;
int vs[205000];
int dep[205000];
int id[105000];
int f[205000][21];
int L[205000];
struct node{
    int ty,x;
};
bool operator<(const node& a,const node& b){
    return id[a.x]<id[b.x];
};
node rec[205000];
int tot;
void dfs(int v,int p,int d,int &k){
    id[v]=k;
    vs[k]=v;
    dep[k++]=d;
    for(int i=0;i<g[v].size();i++){
        if(g[v][i]!=p){
            dfs(g[v][i],v,d+1,k);
            vs[k]=v;
            dep[k++]=d;
        }
    }
}

void rmq_init(int tot){
    for(int i=0;i<tot;i++)f[i][0]=dep[i];
    for(int j=1;j<=20;j++){
        for(int i=0;i+(1<<j)-1<tot;i++){
            f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
        }
    }
}

void init(int V){
    int k=0;
    dfs(1,-1,0,k);
    rmq_init(V*2-1);
}

int query(int a,int b){
    int p=L[b-a+1];
    return min(f[a][p],f[b-(1<<p)+1][p]);
}

int main()
{
    for(int i=1;i<=200000;i++)L[i]=31-__builtin_clz(i);
    while(~scanf("%d%d",&n,&m)){
        for(int i=1;i<=n;i++)g[i].clear();
        for(int i=1;i<n;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        init(n);
        //for(int i=0;i<2*n-1;i++)printf("%d ",vs[i]);
        //printf("\n");
        //for(int i=0;i<2*n-1;i++)printf("%d ",dep[i]);
        //printf("\n");
        //for(int i=1;i<=n;i++)printf("%d ",id[i]);
        //printf("\n");
        while(m--){
            int ans=0;
            tot=0;
            int a;
            scanf("%d",&a);
            for(int i=1;i<=a;i++){
                int x;
                scanf("%d",&x);
                rec[++tot]=(node){1,x};
            }
            int b;
            scanf("%d",&b);
            for(int i=1;i<=b;i++){
                int x;
                scanf("%d",&x);
                rec[++tot]=(node){2,x};
            }
            sort(rec+1,rec+1+tot);
            int am=-1,bm=-1;
            for(int i=1;i<=tot;i++){
                //printf("%d %d\n",rec[i].ty,rec[i].x);
                if(rec[i].ty==1){
                    am=id[rec[i].x];
                    if(bm==-1)continue;
                    ans=max(ans,query(bm,id[rec[i].x]));
                    //printf("%d\n",query(am,id[rec[i].x]));
                }
                else {
                    bm=id[rec[i].x];
                    if(am==-1)continue;
                    ans=max(ans,query(am,id[rec[i].x]));
                    //printf("%d %d %d\n",am,id[rec[i].x],query(am,id[rec[i].x]));
                }
            }
            printf("%d\n",ans+1);
        }
    }
}