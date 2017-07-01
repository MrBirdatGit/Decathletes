#include<bits/stdc++.h>
using namespace std;
const int maxn = 2010;
int head[maxn],tot;
struct edge{
    int to,next;
}e[1000010];
void addedge(int u,int v){
    e[tot].to = v;
    e[tot].next = head[u];
    head[u] = tot++;
}
int b[510][510];
int dfn[maxn],low[maxn],stk[maxn],belong[maxn],top,ins[maxn],clk,scc;
int num[maxn];
int N;
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
        // if(!conn[u][v]) continue;
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
int main(){
    // freopen("a.in","r",stdin);
    int n;
    while(~scanf("%d",&n)){
        int t;
        bool flag = 0;
        N = 2 * n;
        for(int i = 0;i<n;i++){
            for(int j = 0;j<n;j++){
                scanf("%d",&b[i][j]);
            }
        }
        for(int k = 0;k<32;k++){
            init();
            for(int i = 0;i<n;i++){
                for(int j = 0;j<n;j++){
                    if(i == j){
                        if(b[i][i] != 0)
                            flag = 1;
                        continue;
                    }
                    if(i%2 == 1 && j%2 == 1){
                        if(b[i][j] & (1<<k)){
                            addedge(i,j+n);
                            addedge(j,i+n);
                        }else{
                            addedge(i+n,i);
                            addedge(j+n,j);                            
                        }
                    }else if(i%2 == 0 && j%2 == 0){
                        if(b[i][j] & (1<<k)){
                            addedge(i,i+n);
                            addedge(j,j+n);
                        }else{
                            addedge(i+n,j);
                            addedge(j+n,i);               
                        }
                    }else{
                        if(b[i][j] & (1<<k)){
                            addedge(i,j+n);
                            addedge(j,i+n);
                            addedge(i+n,j);
                            addedge(j+n,i);
                        }else{
                            addedge(i,j);
                            addedge(j,i);
                            addedge(i+n,j+n);
                            addedge(j+n,i+n);;                            
                        }
                    }
                }

            }
            if(flag)
                break;
            for(int i = 0;i<N;i++)
                if(!dfn[i])
                    Tarjan(i);
            // for(int i = 0;i<N;i++){
            //     cout<<belong[i]<<' ';
            // }
            // cout<<endl;
            for(int i = 0;i<n;i++){
                if(belong[i] == belong[i+n])
                    flag = 1;
            }
        }
        printf("%s\n",flag?"NO":"YES");
    }

}