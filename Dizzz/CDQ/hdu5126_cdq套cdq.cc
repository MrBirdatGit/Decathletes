#include<bits/stdc++.h>
template <class T>
inline bool rd(T &ret) {
	char c; int sgn;
	if (c = getchar(), c == EOF) return 0;
	while (c != '-' && (c<'0' || c>'9')) c = getchar();
	sgn = (c == '-') ? -1 : 1;
	ret = (c == '-') ? 0 : (c - '0');
	while (c = getchar(), c >= '0'&&c <= '9') ret = ret * 10 + (c - '0');
	ret *= sgn;
	return 1;
}
template <class T>
inline void pt(T x) {
	if (x <0) { putchar('-'); x = -x; }
	if (x>9) pt(x / 10);
    putchar(x % 10 + '0');
    
}
using namespace std;
const int maxn = 50010<<3;
// TODO
int maxl;
struct query{
    int x,y,z,id,op,add;
    query(){}
    query(int _x,int _y,int _z,int _id,int _op,int _add){
        x = _x, y = _y, z = _z, id = _id, op = _op, add = _add;
    }
}qry[maxn],t1[maxn],t2[maxn];
int tot,tot1,tot2;
bool cmp1(query a,query b){
    return a.x == b.x?a.id < b.id:a.x<b.x;
}
bool cmp2(query a,query b){
    return a.y == b.y?a.id < b.id:a.y<b.y;
}
int bit[maxn];
void add(int i,int x){
    while(i<=maxl){
        bit[i] += x;
        i += -i & i;
    }
}
int sum(int i){
    int ret = 0;
    while(i){
        ret += bit[i];
        i -= -i & i;
    }
    return ret;
}
int ans[maxn];
void cdq2(int l,int r){
    tot2 = 0;
    if(l >= r) return;
    int m = (l + r) >> 1;
    for(int i = l;i<=m;i++) if(t1[i].op == 1) t2[++tot2] = t1[i];
    for(int i = m+1;i<=r;i++) if(t1[i].op == 2) t2[++tot2] = t1[i];
    sort(t2+1,t2+tot2+1,cmp2);
    for(int i = 1;i<=tot2;i++){
        if(t2[i].op == 1){
            add(t2[i].z,1);
        }else{
            ans[t2[i].id] += t2[i].add * sum(t2[i].z);
        }
    }
    for(int i = 1;i<=tot2;i++){
        if(t2[i].op == 1)
            add(t2[i].z,-1);
    }
    cdq2(l,m);cdq2(m+1,r);
}
void cdq1(int l,int r){
    if(l >= r) return;
    int m = (l + r) >> 1;
    tot1 = 0;
    for(int i = l;i<=m;i++) if(qry[i].op == 1) t1[++tot1] = qry[i];
    for(int i = m+1;i<=r;i++) if(qry[i].op == 2) t1[++tot1] = qry[i];
    sort(t1+1,t1+tot1+1,cmp1);
    cdq2(1,tot1);
    cdq1(l,m);cdq1(m+1,r);
}
vector<int>vec;
void init(){
    tot = tot1 = tot2 = 0;
    vec.clear();
}
int main(){
    int T;
    rd(T);
    while(T--){
        init();
        int n,op;
        rd(n);
        for(int i = 1;i<=n;i++){
            rd(op);
            if(op == 1){
                ++tot;
                rd(qry[tot].x);rd(qry[tot].y);rd(qry[tot].z);
                vec.push_back(qry[tot].z);
                qry[tot].id = i;qry[tot].op = 1;
                ans[i] = -1;
            }else{
                ans[i] = 0;
                int x1,y1,z1,x2,y2,z2;
                rd(x1);rd(y1);rd(z1);rd(x2);rd(y2);rd(z2);
                qry[++tot] = query(x2  ,y2  ,z2  ,i,2,1);
                qry[++tot] = query(x2  ,y1-1,z1-1,i,2,1);
                qry[++tot] = query(x1-1,y2  ,z1-1,i,2,1);
                qry[++tot] = query(x1-1,y1-1,z2  ,i,2,1);
                qry[++tot] = query(x2  ,y2  ,z1-1,i,2,-1);
                qry[++tot] = query(x2  ,y1-1,z2  ,i,2,-1);
                qry[++tot] = query(x1-1,y2  ,z2  ,i,2,-1);
                qry[++tot] = query(x1-1,y1-1,z1-1,i,2,-1);
                vec.push_back(z2);
                vec.push_back(z1);
                vec.push_back(z1-1);
            }
        }
        sort(vec.begin(),vec.end());
        vec.erase(unique(vec.begin(),vec.end()),vec.end());
        maxl = vec.size();
        for(int i = 1;i<=tot;i++){
            qry[i].z = lower_bound(vec.begin(),vec.end(),qry[i].z) - vec.begin()+1;
        }
        cdq1(1,tot);
        for(int i = 1;i<=n;i++){
            if(ans[i] >= 0)
                pt(ans[i]),putchar('\n');
        }
    }   
    return 0;
}
