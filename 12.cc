#include <bits/stdc++.h>
using namespace std;
int g[1005][1005];
int x[505];
int y[505];
int n;
int main(){
    while(~scanf("%d", &n)){
        memset(g, 0, sizeof(g));
        for(int i=1;i<=n;i++){
            scanf("%d%d", &x[i], &y[i]);
            g[x[i]+500][y[i]+500]=1;
        }
        int ans=0;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                int xd=y[i]-y[j];
                int yd=x[j]-x[i];
                int xa=x[i]+xd;
                int ya=y[i]+yd;
                int xb=x[j]+xd;
                int yb=y[j]+yd;
                if(g[xa+500][ya+500]&&g[xb+500][yb+500])ans++;
		xa=x[i]-xd;
                ya=y[i]-yd;
                xb=x[j]-xd;
                yb=y[j]-yd;
                if(g[xa+500][ya+500]&&g[xb+500][yb+500])ans++;	
            }
        }
	cout<<ans/4<<endl;
    }
}

