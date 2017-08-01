#include<bits/stdc++.h>
#define key ch[ch[root][1]][0]
#define ls ch[x][0]
#define rs ch[x][1]
using namespace std;
const int maxn = 100010;
int sz[maxn],val[maxn],pre[maxn],flip[maxn],ch[maxn][2];
int a[maxn],id[maxn];
int rt,tot;
map<int,int>mp;
void newNode(int &x,int c,int f){
	x = ++tot;
	ls = rs = flip[x] = 0;
	pre[x] = f;
	sz[x] = 1;
	val[x] = c;
}
void up(int x){sz[x] = 1+sz[ls]+sz[rs];}
void down(int x){
	if(flip[x]){
		flip[ls] ^= 1;
		flip[rs] ^= 1;
		swap(ls,rs);
		flip[x] = 0;
	}
}
inline void rotate(int x,int f){  
    int y=pre[x];  
    down(y);  
    down(x);  
    ch[y][!f] = ch[x][f];  
    pre[ ch[x][f] ] = y;  
    pre[x] = pre[y];  
    if(pre[x]) ch[ pre[y] ][ ch[pre[y]][1] == y ] =x;  
    ch[x][f] = y;  
    pre[y] = x;  
    up(y);  
}  
inline void splay(int x,int goal){//将x旋转到goal的下面  
    down(x);//防止pre[x]就是目标点，下面的循环就进不去了，x的信息就传不下去了  
    while(pre[x] != goal){  
        down(pre[pre[x]]); down(pre[x]);down(x);//在旋转之前需要先下传标记，因为节点的位置可能会发生改变  
        if(pre[pre[x]] == goal) rotate(x , ch[pre[x]][0] == x);  
        else   {  
            int y=pre[x],z=pre[y];  
            int f = (ch[z][0]==y);  
            if(ch[y][f] == x) rotate(x,!f),rotate(x,f);  
            else rotate(y,f),rotate(x,f);  
        }  
    }  
    up(x);  
    if(goal==0) rt=x;  
}
void RTO(int k,int goal){//将第k位数旋转到goal的下面  
    int x=rt;  
    down(x);  
    while(sz[ ls ]+1 != k) {  
        if(k < sz[ ls ] + 1 ) x=ls;  
        else {  
            k-=(sz[ ls ]+1);  
            x = rs;  
        }  
        down(x);  
    }  
    splay(x,goal);  
}  
void build(int &x,int l,int r,int f){
	if(l > r) return;
	int m = (l+r)>>1;
	newNode(x,a[m],f);
	mp[id[m]] = x;
	build(ls,l,m-1,x);
	build(rs,m+1,r,x);
	up(x);
}
void init(int n){
	rt = tot = 0;
	ch[0][0] = ch[0][1] = sz[0] = pre[0]= 0;
	flip[0] = val[0] = 0;
	build(rt,1,n,0);
}    
	void vist(int x){  
        if(x){  
            printf("结点%2d : 左儿子  %2d   右儿子  %2d   %2d  flip:%d\n",x,ls,rs,val[x],flip[x]);  
            vist(ls);  
            vist(rs);  
        }  
    } 
void del_root(){  
     int t=rt;  
     if(ch[rt][1]) {  
         rt=ch[rt][1];  
         RTO(1,0);  
         ch[rt][0]=ch[t][0];  
         if(ch[rt][0]) pre[ch[rt][0]]=rt;  
     }  
     else rt=ch[rt][0];  
     pre[rt]=0;  
     up(rt);  
}  
void print(int x,int l,int r){
	if(l>r) return;
	int m = (l+r)>>1;
	cout<<val[x]<<' '<<sz[ls]<<' '<<sz[rs]<<endl;
	print(ls,l,m-1);
	print(rs,m+1,r);
}
vector<pair<int,int> >vec;
int main(){
	int n;
	while(~scanf("%d",&n)){
		if(!n) break;
		vec.clear();
		mp.clear();
		for(int i = 1;i<=n;i++){
			scanf("%d",a+i);
			vec.push_back(make_pair(a[i],i));
		}
		sort(vec.begin(),vec.end());
		for(int i = 0;i<n;i++)
			id[vec[i].second] = i+1;
		init(n);
		for(int i=1;i<=n;i++){
			splay(mp[i],0);
			printf("%d%c",i+sz[ch[rt][0]],i==n?'\n':' ');
			flip[ch[rt][0]]^=1;
			del_root();
		}
	}
}

