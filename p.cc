#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 110;
ll f[maxn][maxn];
ll N;
ll F(ll i,ll j){
	if(f[i][j]) return f[i][j];
	if(i == 1) return f[i][j] = F(1,i-1) + 2*F(1,i-2);	
	ll tmp = 0;	
	for(ll k = j;k<=j+N-1;k++) tmp += F(i-1,k);
	return f[i][j] = tmp;
}
int main(){
	f[1][1]=f[1][2]=1;
	ll n,m;
	while(~scanf("%lld%lld",&n,&m)){
		N = n;
		printf("%lld\n",F(m,1));
	}	
}
