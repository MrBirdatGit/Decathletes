#include<bits/stdc++.h>
using namespace std;
int a[6];
int cal(int num){
    while(num > 1024){
        num -= 1024;
    }
    return num;
}
int main(){
    int n,sum,ans;
    while(~scanf("%d",&n)){
        ans = 0;
        sum = 0;
        for(int i = 1;i<=n;i++){
            scanf("%d",a+i);
            sum += a[i];
        }
        if(n <= 3){
            ans = 1024;
        }else if(n == 4){
            for(int i = 1;i<=4;i++)
                for(int j = i+1;j<=4;j++)
                    for(int k = j + 1;k<=4;k++)
                        if((a[i]+a[j]+a[k]) % 1024 == 0)
                            ans = 1024;
            for(int i = 1;i<=4;i++){
                for(int j = i+1;j<=4;j++){
                    ans = max(ans,cal(a[i]+a[j]));
                }
            }
        }else{
            for(int i = 1;i<=5;i++)
                for(int j = i+1;j<=5;j++)
                    for(int k = j + 1;k<=5;k++){
                        int tmp = a[i] + a[j] + a[k];
                        if(tmp%1024 != 0)
                            continue;
                        tmp = sum - tmp;
                        ans = max(ans,cal(tmp));
                    }
            
        }
        printf("%d\n",ans);
    }
    return 0;
}