#include<bits/stdc++.h>
using namespace std;
const int maxn = 100005;
int bit[maxn];
void add(int i,int x){
    while(i < maxn){
        bit[i] += x;
        i += -i & i;
    }
}
void del(int i){
    while(i < maxn){
        bit[i] = 0;
        i += -i & i;
    }
}
int sum(int i){
    int ret = 0;
    while(i){
        ret += bit[i];
        i -= -i&i;
    }
    return ret;
}
int ans[maxn];
int S[maxn],tp;
struct node{
    int x,y,z,id;
    bool operator <(const node &nd)const{
        if(z != nd.z)
            return z < nd.z;
        if(y != nd.y)
            return y < nd.y;
        return x < nd.x;   
    }
    bool operator == (const node &nd)const{
        return x == nd.x && y == nd.y && z == nd.z;
    }
}x[maxn],x1[maxn];
bool cmp(node a,node b){
    return a.y < b.y;
}
void cdq(int l,int r){
    if(l >= r) return;
    for(int i = l;i<=r;i++){
        x1[i] = x[i];
    }
    int m = (l + r) >> 1;
    sort(x1+l,x1+m+1,cmp);
    sort(x1+m+1,x1+r+1,cmp);
    tp = 0;
    for(int i = m+1,j = l;i<=r;i++){
        while(x1[j].y <= x1[i].y && j <= m){
            add(x1[j].x,1);
            S[tp++] = x1[j].x;
            j++;
        }
        ans[x1[i].id] += sum(x1[i].x);
    }
    for(int i =0 ;i<tp;i++)
        del(S[i]);
    cdq(l,m);
    cdq(m+1,r);
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(ans,0,sizeof(ans));
        memset(bit,0,sizeof(bit));
        int n;
        scanf("%d",&n);
        for(int i = 1;i<=n;i++){
            scanf("%d%d%d",&x[i].x,&x[i].y,&x[i].z);
            x[i].id = i;
        }
        sort(x+1,x+n+1);
        cdq(1,n);
        for(int i = n -1;i>0;i--){
            if(x[i] == x[i+1])
                ans[x[i].id] = ans[x[i+1].id];
        }
        for(int i = 1;i<=n;i++)
            printf("%d\n",ans[i]);
    }
}