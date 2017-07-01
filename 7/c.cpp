#include<bits/stdc++.h>
using namespace std;
int a[110],b[110];
int dif(int a,int b){
    int ret = 0;
    int x = a ^ b;
    for(int i = 0;i<32;i++){
        if(x&(1<<i))
            ret ++;
    }
    return ret;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int n,m;
        scanf("%d%d",&m,&n);
        for(int i = 0;i<m;i++)
            scanf("%d",&a[i]);
        sort(a,a+m);
        for(int i = 0;i<n;i++)
            scanf("%d",&b[i]);
        for(int i = 0;i<n;i++){
            int ans = 0;
            int minn  = 0x3f3f3f3f;
            for(int j = 0;j< m;j++){
                int tmp = dif(b[i],a[j]);
                if(tmp < minn){
                    minn =  tmp;
                    ans =j;
                }
            }
            printf("%d\n",a[ans]);
        }
    }   
}