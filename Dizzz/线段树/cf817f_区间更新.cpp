/*
坑点较多..
之前的RE是因为在底层也可能调用pushdown
至于别人的代码为什么过了..应该是运气比较好..因为所有操作都递归到底的话是一样的
犯了个有点蠢的错误，纠结了一下两种操作的顺序然后就改了pushdown的在update中位置，实际上是不用改的
写线段树的时候思路还是要清晰
*/
#include<bits/stdc++.h>
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define ls rt<<1
#define rs rt<<1|1
#define mid int m = (l + r) >> 1
using namespace std;
typedef long long ll;
const int maxn = 1000005;
int cover[maxn],flag[maxn];
ll cnt[maxn];
int T[maxn],tot;
ll L[maxn],R[maxn],hs[maxn];
void build(int l,int r,int rt){
    cover[rt] = -1;flag[rt] = cnt[rt] = 0;
    if(l == r) return;
    mid;
    build(lson);build(rson);
}
void pushup(int l,int r,int rt){
    cnt[rt] = cnt[ls] + cnt[rs];
}
void pushdown(int l,int r,int rt){
    mid;
    if(cover[rt] != -1){
        cnt[ls] = (m - l + 1)*cover[rt];
        cnt[rs] = (r - m)*cover[rt];
        cover[ls] = cover[rs] = cover[rt];
        flag[ls] = flag[rs] = 0;
        cover[rt] = -1;
    }
    //注意一下标记的处理
    if(flag[rt]){
        cnt[ls] = (m - l + 1) - cnt[ls];
        cnt[rs] = (r - m) - cnt[rs];
        flag[ls] ^=  1;flag[rs] ^= 1;
        flag[rt] = 0;
    }

}
void update(int L,int R,int l,int r,int rt,int x){
    if(L <= l && r <= R){
        if(x == 1){
            cover[rt] = 1;
            cnt[rt] = r - l + 1;
            flag[rt] = 0;
        }else if(x == 2){
            cnt[rt] = cover[rt] = flag[rt] = 0;
        }else{
            flag[rt] ^= 1;
            cnt[rt] = r - l + 1 - cnt[rt];
        }
        return;
    }
    mid;
    pushdown(l,r,rt);
    if(L <= m) update(L,R,lson,x);
    if(m < R) update(L,R,rson,x);
    pushup(l,r,rt);
}
void query(int l,int r,int rt){
    if(l == r){
        printf("%lld\n",hs[l]);
        return;
    }
    mid;
    pushdown(l,r,rt);
    if(cnt[ls] != m - l + 1) query(lson);
    else query(rson);
}
map<ll,int>mp;
int main(){
    int n;
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        scanf("%d%lld%lld",T+i,L+i,R+i);
        R[i]++;
        hs[++tot] = L[i];
        hs[++tot] = R[i];
    }    
    hs[++tot] = 1;//加个1(比如啥都没有的情况)
    hs[++tot] = 1000000000000000005ll;
    sort(hs+1,hs+tot+1);
    tot = unique(hs+1,hs+tot+1)-hs-1;
    for(int i = 1;i<=tot;i++) mp[hs[i]] = i;
    build(1,tot,1);
    for(int i = 0;i<n;i++){
        int l = mp[L[i]];
        int r = mp[R[i]]-1;
        update(l,r,1,tot,1,T[i]);
        query(1,tot,1);
    }
}