#include<bits/stdc++.h>
using namespace std;
const int maxn = 150010;
const int maxm = 1e6+5;
typedef long long ll;
struct query{
    int op,x,y,yy,c,id;
    bool operator<(const query&q)const{
        return x < q.x;
    }
}q[maxn],q1[maxn];
int tot;
ll cnt[maxm<<2];
ll ans[maxn];
int S[maxm],tp;
void up(int x){
    cnt[x] = cnt[x<<1] | cnt[x<<1|1];
}
void build(int x,int l,int r){
    cnt[x] = 0;
    if(l == r) return;
    int m = (l+r)>>1;
    build(x<<1,l,m);build(x<<1|1,m+1,r);
}
void update(int x,int l,int r,int p,int c){
    if(l == r){
        if(cnt[x] == 0){
            S[tp++] = p;
        }
        cnt[x] |= (1LL<<c);
        return;
    }
    int m = (l+r)>>1;
    if(p <= m) update(x<<1,l,m,p,c);
    else update(x<<1|1,m+1,r,p,c);
    up(x);
}
void del(int x,int l,int r,int p){
    cnt[x] = 0;
    if(l == r){
        return;
    }
    int m = (l+r)>>1;
    if(p <= m) del(x<<1,l,m,p);
    else del(x<<1|1,m+1,r,p);
}
ll query(int x,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr){
        return cnt[x];
    }
    ll ret = 0;
    int m = (l+r)>>1;
    if(ql <= m) ret |= query(x<<1,l,m,ql,qr);
    if(qr > m) ret |= query(x<<1|1,m+1,r,ql,qr);
    return ret;
}
int cal(ll x){
    int ret = 0;
    while(x){
        x -= x&-x;
        ret++;
    }
    return ret;
}   
void solve(int l,int r){
    if(l >= r) return;
    int m = (l+r) >> 1;
    for(int i = l;i<=r;i++) q1[i] = q[i];
    tp = 0;
    sort(q1+l,q1+m+1);sort(q1+m+1,q1+r+1);
    for(int i = m+1,j = l;i<=r;i++){
        if(q1[i].op == 1) continue;
        while(j <= m && q1[j].x <= q1[i].x){
            if(q1[j].op == 1)update(1,1,1000000,q1[j].y,q1[j].c);
            j++;
        }
        ans[q1[i].id] |= query(1,1,1000000,q1[i].y,q1[i].yy);
    }
    for(int i = 0;i<tp;i++){
        del(1,1,1000000,S[i]);
    }
    solve(l,m);solve(m+1,r);
}
void init(){
    tot = 0;
    build(1,1,1000000);
    memset(ans,0,sizeof(ans));
}
int main(){
    int op;
    while(~scanf("%d",&op)){
        if(op == 0 || op == 3){
            if(tot != 0){
                solve(1,tot);
                for(int i =1;i<=tot;i++){
                    if(q[i].op == 2) printf("%d\n",cal(ans[q[i].id]));
                }
            }
            if(op == 3) break;
            init();
        }else if(op == 1){
            tot++;
            scanf("%d%d%d",&q[tot].x,&q[tot].y,&q[tot].c);
            q[tot].id = tot;
            q[tot].op = 1;
        }else if(op == 2){
            tot++;
            scanf("%d%d%d",&q[tot].x,&q[tot].y,&q[tot].yy);
            q[tot].op = 2;
            q[tot].id = tot;
        }
    }
}