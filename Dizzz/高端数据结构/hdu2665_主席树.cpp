/*
主席树裸题，主要是要理解主席树的主要思想，用不同的线段树来保存每个前缀的权值和
空间复杂度大概是4*n*log(n)
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
int a[maxn],b[maxn];
int ls[maxn*20],rs[maxn*20],root[maxn*20],cnt[maxn*20],tot;
void build(int l,int r,int &rt){
    rt = ++tot;
    cnt[rt] = 0;
    if(l == r) return;
    int m = (l + r) >> 1;
    build(l,m,ls[rt]);
    build(m+1,r,rs[rt]);
}
void update(int last,int l,int r,int &rt,int p){
    rt = ++tot;
    ls[rt] = ls[last];
    rs[rt] = rs[last];
    cnt[rt] = cnt[last] + 1;
    if(l == r) return;
    int m = (l + r) >> 1;
    if(p <= m) update(ls[last],l,m,ls[rt],p);
    else update(rs[last],m+1,r,rs[rt],p);
}
void query(int ll,int rr,int l,int r,int k){
    if(l == r){
        printf("%d\n",a[l]);
        return;
    }
    int c = cnt[ls[rr]] - cnt[ls[ll]];
    int m = (l + r) >> 1;
    if(k <= c) query(ls[ll],ls[rr],l,m,k);
    else query(rs[ll],rs[rr],m+1,r,k-c);
}
int main(){
    int T,n,m;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i = 1;i<=n;i++){
            scanf("%d",a+i);
            b[i] = a[i];
        }
        sort(a+1,a+1+n);
        int N = unique(a+1,a+1+n)-a-1;
        tot = 0;
        build(1,N,root[0]);
        for(int i = 1;i<=n;i++){
            int p = lower_bound(a+1,a+N+1,b[i]) - a;
            update(root[i-1],1,N,root[i],p);
        }
        int l,r,k;
        while(m--){
            scanf("%d%d%d",&l,&r,&k);
            query(root[l-1],root[r],1,N,k);
        }
    }
}