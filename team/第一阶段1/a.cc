#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
ll n, a0, ax, ay, b0, bx, by;

struct mat{
	ll a[5][5];
	void init(){
		memset(a, 0, sizeof(a));
		a[0][0]=1;
		a[1][0]=ay, a[1][1]=ax;
		a[2][0]=by, a[2][2]=bx;
		a[3][0]=(ay*by)%mod, a[3][1]=(ax*by)%mod, a[3][2]=(ay*bx)%mod, a[3][3]=(ax*bx)%mod;
		a[4][3]=1, a[4][4]=1;
	}
};

mat mul(mat a, mat b){
	mat ans;
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			ans.a[i][j]=0;
			for(int k=0;k<5;k++){
				ans.a[i][j]=(ans.a[i][j]+(a.a[i][k]*b.a[k][j])%mod)%mod;
			}
		}
	}
	return ans;
};

mat power(ll p){
	mat ans;
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			ans.a[i][j]=(i==j);
		}
	}
	mat base;
	base.init();
	while(p){
		if(p&1){
			ans=mul(ans, base);
		}
		p>>=1;
		base=mul(base, base);
	}
	return ans;
};

int main()
{
	while(cin>>n){
		cin>>a0>>ax>>ay>>b0>>bx>>by;
		mat m=power(n);
		ll ans=0;
		ans=(ans+m.a[4][0])%mod;
		ans=(ans+(m.a[4][1]*a0)%mod)%mod;
		ans=(ans+(m.a[4][2]*b0)%mod)%mod;
		ans=(ans+m.a[4][3]*(a0*b0%mod)%mod)%mod;
		cout<<ans<<endl;
	}
}

