#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
ll mult(ll x, ll y, ll mod){
	ll tmp=(x*y-(ll)((long double)x/mod*y)*mod);
	return tmp<0?tmp+mod:tmp;
}

ll a[1050][1050];
ll b[1050][1050];
ll c[1050][1050];
ll t[1050];
ll t1[1050];
ll t2[1050];
ll t3[1050];
int n;

int main(){
	srand(time(NULL));
	scanf("%d", &n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)scanf("%lld", &a[i][j]);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)scanf("%lld", &b[i][j]);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)scanf("%lld", &c[i][j]);
	}
	for(int tst=1;tst<=10;tst++){
		bool ok=true;
		for(int i=1;i<=n;i++)t[i]=rand()%mod;
		memset(t1, 0, sizeof(t1));
		memset(t2, 0, sizeof(t2));
		memset(t3, 0, sizeof(t3));
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				t1[i]=(t1[i]+b[i][j]*t[j])%mod;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				t2[i]=(t2[i]+a[i][j]*t1[j])%mod;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				t3[i]=(t3[i]+c[i][j]*t[j])%mod;
			}
		}
		for(int i=1;i<=n;i++)if(t2[i]!=t3[i])ok=false;
		if(!ok)return 0*printf("NO\n");
	}
	printf("YES\n");
}

