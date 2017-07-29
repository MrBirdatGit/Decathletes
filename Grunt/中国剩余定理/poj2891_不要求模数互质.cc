//解决模线性方程组问题
//不要求模数互质
//2
//8 7
//11 9
//31
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

ll mult(ll x, ll y, ll mod){
	ll tmp=(x*y-(ll)((long double)x/mod*y)*mod);
	return tmp<0?tmp+mod:tmp;
}


ll x, y;
ll ExGCD(ll a, ll b, ll &x, ll &y){
	if(b==0){
		x=1, y=0;
		return a;
	}
	ll d=ExGCD(b, a%b, x, y);
	ll temp=x;
	x=y;
	y=temp-a/b*y;
	return d;
}
ll m1, d1, m2, d2;
int n;

void solve(){
	if(m1==-1)return;
	ll g=__gcd(m1, m2);
	ll M=m1/g*m2;//注意溢出
	if((d2-d1)%g!=0){
		m1=-1;
		return ;
	}
	ExGCD(m1, m2, x, y);
	//printf("%lld\n", x);
	x=(d2-d1)/g*x;
	//printf("%lld\n", x);
	d1=((mult(m1, x, M)+d1)%M+M)%M;//注意溢出
	m1=M;
}

int main()
{
	while(~scanf("%d", &n)){
		scanf("%lld %lld", &m1, &d1);
		for(int i=2;i<=n;i++){
			scanf("%lld %lld", &m2, &d2);
			solve();
		}
		if(m1==-1)printf("-1\n");
		else printf("%lld\n", (d1%m1+m1)%m1);
	}
}

