#include <bits/stdc++.h>
using namespace std;
int g[600][600];
int n;

void solve(int x,int y,int siz,int typ,int num){
    if(siz%2==0){
        if(typ==1){
            if(siz==2){
                g[x][y]=num;
                g[x][y+1]=num+1;
                g[x+1][y+1]=num+2;
                g[x+1][y]=num+3;
                return ;
            }
            for(int i=1;i<=siz-2;i++){
                if(i%2==1)g[x+i-1][y]=num+(i/2)*4;
                else g[x+i-1][y]=g[x+i-2][y]+3;
                if(i%2==1)g[x+i-1][y+1]=g[x+i-1][y]+1;
                else g[x+i-1][y+1]=g[x+i-2][y+1]+1;
            }
            for(int j=1;j<=siz;j++){
                if(j%2==1)g[x+siz-2][y+j-1]=g[x+siz-3][y]+1+(j/2)*4;
                else g[x+siz-2][y+j-1]=g[x+siz-2][y+j-2]+3;
                if(j%2==1)g[x+siz-1][y+j-1]=g[x+siz-2][y+j-1]+1;
                else g[x+siz-1][y+j-1]=g[x+siz-1][y+j-2]+1;
            }
            solve(x,y+2,siz-2,typ^1,num+4*siz-4);
        }
        else {
            if(siz==2){
                g[x+1][y+1]=num;
                g[x+1][y]=num+1;
                g[x][y]=num+2;
                g[x][y+1]=num+3;
                return;
            }
             int xr=2*x+siz-1;
                int yr=2*y+siz-1;
            for(int i=1;i<=siz-2;i++){
               
                if(i%2==1)g[xr-(x+i-1)][yr-y]=num+(i/2)*4;
                else g[xr-(x+i-1)][yr-y]=g[xr-(x+i-2)][yr-y]+3;
                if(i%2==1)g[xr-(x+i-1)][yr-(y+1)]=g[xr-(x+i-1)][yr-y]+1;
                else g[xr-(x+i-1)][yr-(y+1)]=g[xr-(x+i-2)][yr-(y+1)]+1;
            }
            for(int j=1;j<=siz;j++){
                if(j%2==1)g[xr-(x+siz-2)][yr-(y+j-1)]=g[xr-(x+siz-3)][yr-y]+1+(j/2)*4;
                else g[xr-(x+siz-2)][yr-(y+j-1)]=g[xr-(x+siz-2)][yr-(y+j-2)]+3;
                if(j%2==1)g[xr-(x+siz-1)][yr-(y+j-1)]=g[xr-(x+siz-2)][yr-(y+j-1)]+1;
                else g[xr-(x+siz-1)][yr-(y+j-1)]=g[xr-(x+siz-1)][yr-(y+j-2)]+1;
            }
            solve(x+2,y,siz-2,typ^1,num+4*siz-4);
        }
    }
    else {
        if(typ==1){
            if(siz==1){
                g[x][y]=num;
                return ;
            }
            for(int i=1;i<=siz;i++){
                if(i%2==1)g[x+i-1][y]=num+(i/2)*4;
                else g[x+i-1][y]=g[x+i-2][y]+3;
                if(i%2==1)g[x+i-1][y+1]=g[x+i-1][y]+1;
                else g[x+i-1][y+1]=g[x+i-2][y+1]+1;
            }
            for(int j=3;j<=siz;j++){
                if(j%2==1)g[x+siz-2][y+j-1]=g[x+siz-1][y+1]+2+(j-3)/2*4;
                else g[x+siz-2][y+j-1]=g[x+siz-2][y+j-2]+1;
                if(j%2==1)g[x+siz-1][y+j-1]=g[x+siz-1][y+1]+1+(j-3)/2*4;
                else g[x+siz-1][y+j-1]=g[x+siz-1][y+j-2]+3;
            }
            solve(x,y+2,siz-2,typ^1,num+4*siz-4);
        }
        else {
            if(siz==1){
                g[x][y]=num;
                return;
            }
            int xr=2*x+siz-1;
            int yr=2*y+siz-1;
            for(int i=1;i<=siz;i++){
                if(i%2==1)g[xr-(x+i-1)][yr-y]=num+(i/2)*4;
                else g[xr-(x+i-1)][yr-y]=g[xr-(x+i-2)][yr-y]+3;
                if(i%2==1)g[xr-(x+i-1)][yr-(y+1)]=g[xr-(x+i-1)][yr-y]+1;
                else g[xr-(x+i-1)][yr-(y+1)]=g[xr-(x+i-2)][yr-(y+1)]+1;
            }
            for(int j=3;j<=siz;j++){
                if(j%2==1)g[xr-(x+siz-2)][yr-(y+j-1)]=g[xr-(x+siz-1)][yr-(y+1)]+2+(j-3)/2*4;
                else g[xr-(x+siz-2)][yr-(y+j-1)]=g[xr-(x+siz-2)][yr-(y+j-2)]+1;
                if(j%2==1)g[xr-(x+siz-1)][yr-(y+j-1)]=g[xr-(x+siz-1)][yr-(y+1)]+1+(j-3)/2*4;
                else g[xr-(x+siz-1)][yr-(y+j-1)]=g[xr-(x+siz-1)][yr-(y+j-2)]+3;
            }
            solve(x+2,y,siz-2,typ^1,num+4*siz-4);
        }
    }
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        solve(1,1,n,1,1);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)printf("%d%c",g[i][j],j==n?'\n':' ');
        }
    }
}
