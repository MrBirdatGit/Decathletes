#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cstdio>
typedef long long ll;
const ll mod = 1e9+7;
using namespace std;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ll n,k,s =0;
        scanf("%lld%lld",&n,&k);
        for(ll i = 1;i<=n;i++){
            ll p = 1;
            for(int j = 0;j<k;j++)
                p = (i*p)%mod;
            s = (s + p)%mod;
        }
        printf("%lld\n",s);
    }
}