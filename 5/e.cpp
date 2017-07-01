#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 200010;
typedef long long ll;
struct edge{
    int u,v;
    ll w;
    bool operator<(const edge&E)const{
        return w > E.w;
    }
}e[maxn];
int F[maxn];
ll num[maxn];
ll sum[maxn];
int Find(int x){
    if(F[x] != x)
        return F[x] = Find(F[x]);
    return x;
}
void Union(int x,int y,ll cap){
    int x1 = Find(x);
    int y1 = Find(y);
    if(x1 == y1) return;
    if(sum[x1] + cap * num[y1] > sum[y1] + cap * num[x1]){
        F[y1] = x1;
        num[x1] += num[y1];
        sum[x1] += cap * num[y1];
    }else{
        F[x1] = y1;
        num[y1] += num[x1];
        sum[y1] += cap * num[x1];
    }
}
int main(){
    int n;
    while(~scanf("%d",&n)){
        for(int i = 1;i<=n;i++){
            F[i] = i;
            sum[i] = 0;
            num[i] = 1;
        }
        for(int i = 1;i<n;i++)
            scanf("%d%d%lld",&e[i].u,&e[i].v,&e[i].w);
        sort(e+1,e+n);
        for(int i = 1;i<n;i++){
            Union(e[i].u,e[i].v,e[i].w);
        }
        for(int i = 1;i<=n;i++){
            if(F[i] == i){
                printf("%lld\n",sum[i]);
            }
        }
    }
}