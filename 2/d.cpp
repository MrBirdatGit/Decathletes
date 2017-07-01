#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF=1e6;
const int mod=1e9+7;
int n;
char str[60][60];
int g[60][60];
int d[60][60];
int dis[60];
bool visited[60];
void dijkstra(){
    memset(d[1],0x3f,sizeof(d[1]));
    memset(visited,0,sizeof(visited));
    d[1][1] = 0;
    while(1){
        int mini = -1;
        for(int i = 1;i<=n;i++)
            if(!visited[i] && (mini==-1 || d[1][i] < d[1][mini]))
                mini = i;
        if(mini == -1) break;
        visited[mini] = 1;
        for(int  i = 2;i<=n;i++)
            d[1][i] = min(d[1][i],d[1][mini] + g[mini][i]);
    }
}
int main()
{
    while(~scanf("%d",&n)){
        for(int i=1;i<=n;i++){
            scanf("%s",str[i]+1);
            for(int j=1;j<=n;j++){
                g[i][j]=str[i][j]-'0';
                if(g[i][j]==0&&i!=j)g[i][j]=INF;
                d[i][j]=g[i][j];
            }
        }
        // for(int k=1;k<=n;k++){
        //     for(int i=1;i<=n;i++){
        //         for(int j=1;j<=n;j++){
        //             if(d[i][j]<INF&&d[k][j]<INF){
        //                 d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
        //             }
        //         }
        //     }
        // }
        dijkstra();
        // for(int i=1;i<=n;i++)printf("%d\n",d[1][i]);
        bool ok=true;
        for(int i=2;i<=n;i++)if(d[1][i]>=INF)ok=false;
        if(!ok){
            printf("0\n");
            continue;
        }
        ll ans=1;
        for(int i=2;i<=n;i++){
            int tans=0;
            for(int j=1;j<=n;j++){
                if(j==i)continue;
                if(d[1][i]-d[1][j]==g[i][j]){
                    tans++;
                }
            }
            ans=(ans*tans)%mod;
        }
        printf("%lld\n",ans);
    }
}
