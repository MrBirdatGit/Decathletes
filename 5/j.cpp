#include<bits/stdc++.h>
using namespace std;
const int maxn = 210000;
struct rect{
    int ls,rs;
    int xl,yl,xr,yr;
    void setv(int xl,int yl,int xr,int yr){
        this->xl = xl;
        this->yl = yl;
        this->xr = xr;
        this->yr = yr;
        this->ls = this->rs = -1;
    }
    friend istream & operator >>(istream& i, rect &v){
        i >> v.xl >>v.yl>> v.xr>> v.yr ;
        return i ;
    }
    friend ostream & operator <<(ostream& i, rect &v){
        i << v.xl << ' ' << v.yl << ' ' <<v.xr<<' '<<v.yr;
        return i ;
    }
}node[maxn];
int tot;
int find(int root,int x,int y)
{
    int tmp=root,tt;
    while(1)
    {
        if(node[tmp].ls == -1)return tmp;
        tt=node[tmp].ls;
        if(x<=node[tt].xr&&x>=node[tt].xl&&y>=node[tt].yl&&y<=node[tt].yr)tmp=tt;
        else tmp=node[tmp].rs;
    }
}
int parent[maxn];
int depth[maxn];
int num[maxn];
int dfs(int v,int p,int d){
    num[v] = 0;
    parent[v] =p;
    depth[v] = d;
    if(node[v].ls == -1)
        return num[v] = 1;
    else{
        num[v] += dfs(node[v].ls,v,d+1);
        num[v] += dfs(node[v].rs,v,d+1);
    }
    return num[v];
}
int lca(int u,int v){
    while(depth[u] > depth[v]){
        u = parent[u];
    }
    while(depth[v] > depth[u]){
        v = parent[v];
    }
    while( u != v){
        u = parent[u];
        v = parent[v];
    }
    return u;
}
int main(){
    rect tmp;
    int xa,ya,xb,yb;
    int n,q;
    while(cin>>node[0]){
        tot = 1;
        node[0].ls = node[1].rs = -1;
        cin>>n>>q;
        for(int cs = 1;cs<=n;cs++){
            cin>>xa>>ya>>xb>>yb;
            if(xa > xb) swap(xa,xb);
            if(ya > yb) swap(ya,yb);
            int j = find(0,(xa+xb)/2,(ya+yb)/2);
            node[tot].setv(node[j].xl,node[j].yl,xb,yb);
            node[j].ls = tot;
            tot++;
            node[tot].setv(xa,ya,node[j].xr,node[j].yr);
            node[j].rs= tot;
            tot++;


        }
        dfs(0,-1,0);
        while(q--){
            cin>>xa>>ya>>xb>>yb;
            int p1 = find(0,xa,ya),p2 = find(0,xb,yb);
            int ret = lca(p1,p2);
            cout<<n+2-num[ret]<<endl;
        }
    }
}