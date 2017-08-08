#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a,b;
ll x,y;
ll extgcd(ll a,ll b,ll &x,ll &y){
	ll d=a;
	if(b!=0){
		d=extgcd(b,a%b,y,x);
		y-=(a/b)*x;
	}else {
		x=1;y=0;
	}
	return d;
}
int main(){
	scanf("%lld%lld",&a,&b);
	if(a==1&&b==1)return 0*printf("1\n");
	if(a==1||b==1)return 0*printf("2\n");
	if(__gcd(a,b)!=1)return 0*printf("%lld\n",a*b/__gcd(a,b));
	ll ans=a*b;
	extgcd(a,b,x,y);
	x%=b;
	x-=b;
	while(a*x<=1)x+=b;
	ans=min(ans,a*x);
	extgcd(b,a,y,x);
	y%=a;
	y-=a;
	while(b*y<=1)y+=a;
	ans=min(ans,b*y);
	printf("%lld\n",ans);
}
