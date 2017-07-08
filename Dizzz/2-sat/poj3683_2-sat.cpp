#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int maxn = 2010;
const int maxm = maxn * maxn;
int head[maxn],tot;
struct edge{
    int to,next;
}e[maxm];
void addedge(int u,int v){
    e[tot].to = v;
    e[tot].next = head[u];
    head[u] = tot++;
}
int dfn[maxn],low[maxn],stk[maxn],belong[maxn],top,ins[maxn],clk,scc,num[maxn];
void init(){
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(ins,0,sizeof(ins));
    tot = top = clk = scc = 0;
}
void Tarjan(int u){
    int v;
    dfn[u] = low[u] = ++clk;
    stk[top++] = u;
    ins[u] = 1;
    for(int i = head[u];i!=-1;i=e[i].next){
        int v = e[i].to;
        if(!dfn[v]){
            Tarjan(v);
            low[u] = min(low[u],low[v]);
        }else if(ins[v]){
            low[u] = min(low[u],dfn[v]);
        }
    }
    if(low[u] == dfn[u]){
        scc++;
        do{
            v = stk[--top];
            ins[v] = 0;
            belong[v] = scc;
            num[scc]++;
        }while(u != v);
    }
}
int s[maxn],t[maxn],d[maxn];
int main(){
	int n,s1,s2,t1,t2;
	init();
	scanf("%d",&n);
	for(int i = 0;i<n;i++){
		scanf("%d:%d %d:%d %d",&s1,&s2,&t1,&t2,d+i);
		s[i] = s1 * 60 + s2;
		t[i] = t1 * 60 + t2;
	}
	for(int i = 0;i<n;i++){
		for(int j = 0;j<i;j++){
			if(min(s[i]+d[i],s[j]+d[j]) > max(s[i],s[j])){
				addedge(i,n+j);
				addedge(j,n+i);
			}
			if(min(s[i]+d[i],t[j]) > max(s[i],t[j]-d[j])){
				addedge(i,j);
				addedge(n+j,n+i);
			}
			if(min(t[i],s[j]+d[j]) > max(t[i]-d[i],s[j])){
				addedge(n+i,n+j);
				addedge(j,i);
			}
			if(min(t[i],t[j]) > max(t[i]-d[i],t[j]-d[j])){
				addedge(n+i,j);
				addedge(n+j,i);
			}
		}
	}
	int N = 2 * n;
	for(int i = 0;i<N;i++)
		if(!dfn[i])
			Tarjan(i);
	for(int i = 0;i<n;i++){
		if(belong[i] == belong[i+n]){
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n");
	//�ƺ�����Ҫ��������
	for(int i = 0;i<n;i++){
		if(belong[i] < belong[i+n])
			printf("%02d:%02d %02d:%02d\n",s[i]/60,s[i]%60,(s[i]+d[i])/60,(s[i]+d[i])%60);
		else
			printf("%02d:%02d %02d:%02d\n",(t[i]-d[i])/60,(t[i]-d[i])%60,t[i]/60,t[i]%60);
	}

}
