#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define mid int m = (l+r)>>1;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define ls rt<<1
#define rs rt<<1|1
using namespace std;
const int maxn = 210;
struct line{
    double l, r, pos, add;
    void seti(double l, double r, double pos, double add){
        this->l=l;this->r=r;this->pos=pos;this->add=add;
    }
    bool operator<(const line&l)const{return pos<l.pos;}
}li[maxn];
double hs[maxn];
int tot;
int flag[maxn<<4];
double sum[maxn<<4];

void pushup(int l,int r,int rt){    
    if(flag[rt]) sum[rt] = hs[r] - hs[l-1];
    else if(l == r) sum[rt] = 0;
    else sum[rt] = sum[ls] + sum[rs];
}
void bulid(){    
    memset(flag,0,sizeof(flag));
    memset(sum,0,sizeof(sum));
}
void update(int L,int R,int l,int r,int rt,int x){
    if(L <= l && r <= R){
        flag[rt] += x;
        pushup(l,r,rt);
        return;
    }
    mid;
    if(L <= m) update(L,R,lson,x);
    if(R > m) update(L,R,rson,x);
    pushup(l,r,rt);
}
int main(){
    int n;
    int cs = 0;
    double x1,y1,x2,y2;
    while(~scanf("%d", &n)){
        if(!n) break;
        tot = 0;
        for(int i = 0;i<n;i++){
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            hs[tot] = y1;
            hs[tot+1] = y2;
            li[tot++].seti(y1, y2,x1,1);
            li[tot++].seti(y1, y2,x2,-1);
        }
        sort(li,li+tot);
        sort(hs,hs+tot);
        int hh = unique(hs, hs+tot) - hs;
        double ans = 0;
        bulid();
        for(int i = 0;i<tot-1;i++){
            int l = lower_bound(hs,hs+hh,li[i].l)-hs;
            int r = lower_bound(hs,hs+hh,li[i].r)-hs;
            update(l+1,r,1,hh,1,li[i].add);
            ans += (li[i+1].pos - li[i].pos) * sum[1];
        }
        printf("Test case #%d\n",++cs);
        printf("Total explored area: %.2lf\n\n",ans);
    }
}
