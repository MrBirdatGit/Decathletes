//顺序三元组个数
//树状数组水题
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
int a[20500];
int c[105000];

int pres[20500];
int prel[20500];
int sufs[20500];
int sufl[20500];

int lowbit(int x){
	return x&(-x);
}

void update(int x){
	while(x<=100000){
		c[x]++;
		x+=lowbit(x);
	}
}

int query(int x){
	int ans=0;
	while(x){
		ans+=c[x];
		x-=lowbit(x);
	}
	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i=1;i<=n;i++){
			scanf("%d", &a[i]);
		}
		memset(c, 0, sizeof(c));
		for(int i=1;i<=n;i++){
			pres[i]=query(a[i]);
			prel[i]=i-1-pres[i];
			update(a[i]);
		}
		memset(c, 0, sizeof(c));
		for(int i=n;i>=1;i--){
			sufs[i]=query(a[i]);
			sufl[i]=n-i-sufs[i];
			update(a[i]);
		}
		ll ans=0;
		for(int i=1;i<=n;i++){
			ans+=1LL*pres[i]*sufl[i]+1LL*prel[i]*sufs[i];
		}
		printf("%lld\n", ans);
	}
}

