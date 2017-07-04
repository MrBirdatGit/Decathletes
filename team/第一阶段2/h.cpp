#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;

struct mat{
    ll a[3][3];
};
mat mul(mat a,mat b){
    mat ans;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            ans.a[i][j]=0;
            for(int k=0;k<3;k++){
                ans.a[i][j]=(ans.a[i][j]+a.a[i][k]*b.a[k][j])%mod;
            }
        }
    }
    return ans;
}

mat power(ll n){
    mat base;
    for(int i=0;i<3;i++)for(int j=0;j<3;j++)base.a[i][j]=0;
    base.a[0][0]=base.a[0][2]=base.a[1][0]=base.a[2][1]=1;
    mat ans;
    for(int i=0;i<3;i++)for(int j=0;j<3;j++)ans.a[i][j]=(i==j);
    while(n){
        if(n&1){
            ans=mul(ans,base);
        }
        n>>=1;
        base=mul(base,base);
    }
    return ans;
}


int main()
{
    int t;
    cin>>t;
    while(t--){
        ll n;
        cin>>n;
        mat ans=power(n-2);
        ll an=0;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                //printf("%d",ans.a[i][j]);
                an=(an+ans.a[i][j])%mod;
            }
            //printf("\n");
        }
        cout<<an<<endl;
    }
}