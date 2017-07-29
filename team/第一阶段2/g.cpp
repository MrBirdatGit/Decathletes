#include <bits/stdc++.h>
using namespace std;
int t,n;
int a[105000];
bool vis[105000];
int fa[105000];
int getfa(int x){
    if(x==fa[x])return x;
    return getfa(fa[x]);
}
int main()
{
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=2;i<=n;i++)scanf("%d",&a[i]);
        fa[n+1]=n+1;
        for(int i=n;i>=1;i--){
            if(a[i]==1)fa[i]=i;
            else fa[i]=fa[i+1];
        }
        memset(vis,false,sizeof(vis));
        for(int i=1;i<=n;i++){
            if(vis[i])continue;
            if(i==n)break;
            int p=getfa(i+1);
            //printf("%d %d\n",i,p);
            if(p<=n){
                vis[i]=true;
                vis[p]=true;
                fa[p]=getfa(p+1);
            }
            else break;
        }
        bool ok=true;
        for(int i=1;i<=n;i++)if(!vis[i])ok=false;
        if(ok)printf("Yes\n");
        else printf("No\n");
    }
}
