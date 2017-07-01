#include<bits/stdc++.h>
#define mid int m = (l+r)>>1;
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
#define ls rt<<1
#define rs rt<<1|1
using namespace std;
typedef long long ll;
int M, N, tot;
ll W, H;
const int maxn = 100001;
struct node{
    int xl,yl,xr,yr;
}rec[maxn];
struct line{
    int l,r,pos,add;
    line(){}
    line(int l,int r,int pos,int add):l(l),r(r),pos(pos),add(add){}
    bool operator < (const line &l)const{
        return pos < l.pos;
    }
};
vector<line>li;
vector<int>hs;
int flag[maxn<<2],sum[maxn<<2];
void pushup(int l, int r, int rt){
    if(flag[rt]) sum[rt] = hs[r] - hs[l-1];
    else if(l == r) sum[rt] = 0;
    else sum[rt] = sum[ls] + sum[rs];
}
void bulid(int l, int r, int rt){
    memset(flag,0,sizeof(flag));
    memset(sum,0,sizeof(sum));
}
void update(int L, int R, int l, int r, int rt, int x){
    if(L <= l && r <= R){
        flag[rt] += x;
        pushup(l,r,rt);
        return;
    }
    mid;
    if(L<=m) update(L, R, lson, x);
    if(m < R) update(L, R, rson,x);
    pushup(l, r, rt);
}
ll solve(){
    if(N == 0){
        return H * (W - M + 1);
    }
    ll ret =0 ;
    sort(li.begin(),li.end());
    sort(hs.begin(),hs.end());
    hs.erase(unique(hs.begin(),hs.end()),hs.end());
    int sz = li.size() - 1;
    int hh = hs.size();
    bulid(1,hh,1);
    for(int i = 0;i<sz;i++){
        int l = lower_bound(hs.begin(),hs.end(),li[i].l) - hs.begin();
        int r = lower_bound(hs.begin(),hs.end(),li[i].r) - hs.begin();
        update(l+1,r,1,hh,1,li[i].add);
        ret +=(ll)sum[1]* (li[i+1].pos - li[i].pos) ;        
    }
    return W * H - ret;
}
int main(){
    while(~scanf("%lld%lld%d%d", &W, &H, &N, &M)){
        ll ans = 0;
        for(int i=1;i<=N;i++){
            scanf("%d%d%d%d", &rec[i].xl, &rec[i].yl, &rec[i].xr, &rec[i].yr);
            rec[i].xl--;
            rec[i].yl--;
        }
        li.clear();
        hs.clear();
        for(int i = 1;i<=N;i++){
            li.push_back(line(max(0,rec[i].yl-M+1),rec[i].yr,rec[i].xl , 1));
            li.push_back(line(max(0,rec[i].yl-M+1),rec[i].yr,rec[i].xr , -1));
            hs.push_back(li[li.size()-1].l);
            hs.push_back(li[li.size()-1].r);
        }
        li.push_back(line(max(0,(int)H-M+1),H,0,1));
        li.push_back(line(max(0,(int)H-M+1),H,W,-1));
        hs.push_back(li[li.size()-1].l);
        hs.push_back(li[li.size()-1].r);
        ans += solve();
        swap(H,W);
        li.clear();
        hs.clear();
        for(int i = 1;i<=N;i++){
            li.push_back(line(max(0,rec[i].xl-M+1),rec[i].xr,rec[i].yl , 1));
            li.push_back(line(max(0,rec[i].xl-M+1),rec[i].xr,rec[i].yr , -1));
            hs.push_back(li[li.size()-1].l);
            hs.push_back(li[li.size()-1].r);
        }
        li.push_back(line(max(0,(int)H-M+1),H,0,1));
        li.push_back(line(max(0,(int)H-M+1),H,W,-1));
        hs.push_back(li[li.size()-1].l);
        hs.push_back(li[li.size()-1].r);
        ans += solve();
        if(M == 1)
            ans /= 2;
        printf("%lld\n",ans);
    }
}