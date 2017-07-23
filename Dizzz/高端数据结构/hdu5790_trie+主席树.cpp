/*
求n个字符串中[l,r]的字符串不同前缀的数量
字典树记录前缀的上一次出现位置，问题转化为求[l,r]中该值小于l的个数，主席树实现
*/ 
#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
int n;
int pre[maxn];
int cnt;
struct Trie{
    int ch[maxn][26],val[maxn],sz;
    void init(){
        memset(ch[0],0,sizeof(ch[0]));
        memset(val,0,sizeof(val));
        sz = 1;
    }
    void insert(char *s,int id){
        int len = strlen(s),u = 0;
        for(int i = 0;i<len;i++){
            int c = s[i] - 'a';
            if(!ch[u][c]){
                val[sz] = 0;
                memset(ch[sz],0,sizeof(ch[sz]));
                ch[u][c] = sz++;
            }
            u = ch[u][c];
            pre[++cnt] = val[u];
            val[u] = id;
        }
    }
}trie;
struct CMT{
    int ls[maxn*30],rs[maxn*30],sum[maxn*30],root[maxn*30],tot;
    void init(){tot = 0;}
    void build(int l,int r,int &rt){
        rt = ++tot;
        sum[rt] = 0;
        if(l == r) return;
        int m = (l+r)>>1;
        build(l,m,ls[rt]);
        build(m+1,r,rs[rt]);
    }
    void update(int last,int l,int r,int &rt,int p){
        rt = ++tot;
        ls[rt] = ls[last];
        rs[rt] = rs[last];
        sum[rt] = sum[last] + 1;
        if(l == r) return;
        int m = (l + r)>>1;
        if(p <= m) update(ls[last],l,m,ls[rt],p);
        else update(rs[last],m+1,r,rs[rt],p);
    }
    int query(int ll,int rr,int l,int r,int p){
        if(l == r) return sum[rr] - sum[ll];
        int m = (l + r) >>1;
        if(p <= m) return query(ls[ll],ls[rr],l,m,p);
        else return sum[ls[rr]] - sum[ls[ll]] + query(rs[ll],rs[rr],m+1,r,p);
    }
    void print(int l,int r,int rt){
        cout<<l<<' '<<r<<' '<<sum[rt]<<endl;
        if(l == r) return;
        int m = (l+r)>>1;
        print(l,m,ls[rt]);
        print(m+1,r,rs[rt]);
    }
}cmt;
char str[maxn];
int s[maxn],e[maxn];
int main(){
    while(~scanf("%d",&n)){
        trie.init();
        cnt = 0;
        for(int i = 1;i<=n;i++){
            scanf("%s",str);
            s[i] = cnt + 1;
            trie.insert(str,i);
            e[i] = cnt;
        }
        cmt.init();
        cmt.build(0,n,cmt.root[0]);
        for(int i = 1;i<=cnt;i++){
            cmt.update(cmt.root[i-1],0,n,cmt.root[i],pre[i]);
        }
        int z = 0,l,r,m;
        scanf("%d",&m);
        while(m--){
            scanf("%d%d",&l,&r);
            int L = min((z+l)%n,(z+r)%n)+1;
            int R = max((z+l)%n,(z+r)%n)+1;
            printf("%d\n",z = cmt.query(cmt.root[s[L]-1],cmt.root[e[R]],0,n,L-1));
        }
    }
}