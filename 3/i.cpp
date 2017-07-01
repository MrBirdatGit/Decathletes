#include <bits/stdc++.h>
using namespace std;
int main()
{
    int T;
    char s[10];
    int n;
    scanf("%d",&T);
    while(T--){
        scanf("%d %s",&n,s);
        double ans = 0;
        int x;
        for(int i = 0;i<n;i++){
            scanf("%d",&x);
            double t = x/100.0;
            if(x == 0){
                continue;
            }else if(s[0] == 'b'){
                ans -= double(t)*log(t)/log(2);
            }else if(s[0] == 'n'){
                ans -= double(t)*log(t);
            }else{
                ans -= double(t)*log(t)/log(10);
            }
        }
        printf("%.12lf\n",ans);
    }
}
