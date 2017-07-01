#include <bits/stdc++.h>
using namespace std;
int gcd(int x,int y){
    if(y==0)return x;
    return gcd(y,x%y);
}

int a[105000];
int b[105000];
int c[105000];
int main()
{
    int t;
    cin>>t;
    while(t--){
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        b[0]=0;
        for(int i=1;i<=n;i++)b[i]=gcd(b[i-1],a[i]);
        c[n+1]=0;
        for(int i=n;i>=1;i--)c[i]=gcd(c[i+1],a[i]);
        int ans=0;
        for(int i=1;i<=n;i++)ans=max(ans,gcd(b[i-1],c[i+1]));
        printf("%d\n",ans);    
    } 
}
