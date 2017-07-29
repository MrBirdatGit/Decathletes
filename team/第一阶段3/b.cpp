#include <bits/stdc++.h>
using namespace std;
vector<int>g[205000];
bool vis[205000];
int tag[205000];
int path[205000];
int rec[205000];
int ma[205000];
int mb[205000];

int ans,ansa,ansb;
int n,t;
int st,ed;
int len;
bool ok=false;
int tmp;

void dfs3(int u,int dep){
    tmp=max(tmp,dep);
    vis[u]=true;
    for(int i=0;i<g[u].size();i++){
        int v=g[u][i];
        if(!vis[v])dfs3(v,dep+1);
    }
    
}

void solve(){
    memset(vis,false,sizeof(vis));
    //for(int i=0;i<len;i++)printf("%d ",path[i]);
    //printf("\n");
    for(int i=0;i<len;i++)vis[path[i]]=true;
    for(int i=0;i<len;i++){
        tmp=0;
        dfs3(path[i],0);
        rec[i]=tmp;
    }
    //for(int i=0;i<len;i++)printf("%d ",rec[i]);
    //printf("\n");
    ma[0]=1;
    int pp=1;
    for(int i=1;i<len;i++){
        pp=max(pp,i+1+rec[i]);
        ma[i]=pp;
    }
    mb[len-1]=1;
    pp=1;
    for(int i=len-2;i>=0;i--){
        pp=max(pp,len-i+rec[i]);
        mb[i]=pp;
    }
    ans=1e9;
    int qie=0;
    for(int i=0;i<=len-2;i++){
        if(ans>max(ma[i],mb[i+1])){
            ans=max(ma[i],mb[i+1]);
            qie=i;
        }
    }
    ans/=2;
    ansa=min(ans,qie);
    ansb=max(qie+1,len-1-ans);
    ansa=path[ansa];
    ansb=path[ansb];
}


void dfs1(int u,int dep){
    vis[u]=true;
    tag[u]=dep;
    for(int i=0;i<g[u].size();i++){
        int v=g[u][i];
        if(!vis[v])dfs1(v,dep+1);
    }
}

void dfs2(int u,int dep){
    if(ok)return ;
    vis[u]=true;
    path[dep]=u;
    if(u==ed){
        ok=true;
        solve();
        return ;
    }
    for(int i=0;i<g[u].size();i++){
        int v=g[u][i];
        if(!vis[v])dfs2(v,dep+1);
    }
}

int main()
{
    scanf("%d",&t);
    while(t--){
        ok=false;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)g[i].clear();
        for(int i=1;i<n;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        memset(vis,false,sizeof(vis));
        dfs1(1,0);
        st=1;
        for(int i=1;i<=n;i++)if(tag[i]>tag[st])st=i;
        memset(vis,false,sizeof(vis));
        dfs1(st,0);
        ed=1;
        for(int i=1;i<=n;i++)if(tag[i]>tag[ed])ed=i;
        len=tag[ed]+1;
        memset(vis,false,sizeof(vis));
        dfs2(st,0);
        printf("%d %d %d\n",ans,ansa,ansb);
    }
}
