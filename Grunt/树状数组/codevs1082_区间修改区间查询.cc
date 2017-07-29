//树状数组区间修改区间查询
//sum[n]=sigma(a[i])+sigma((n+1-i)d[i]);
//其中a[i]是原数组元素
//d[i]是[i, n]的共同增量
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[205000];
ll d[205000];
ll di[205000];
int n, q;

int lowbit(int x){
	return x&(-x);
}

void update(int x, int num){
	ll add=1LL*num;
	ll addi=1LL*num*x;
	while(x<=n){
		d[x]+=add;
		di[x]+=addi;
		x+=lowbit(x);
	}
}

ll query(int x){
	ll ans=a[x];
	ll tmp=x;
	while(tmp){
		ans+=d[tmp]*(x+1);
		ans+=di[tmp]*(-1);
		tmp-=lowbit(tmp);
	}
	return ans;
}

int main()
{
	scanf("%d", &n);
	for(int i=1;i<=n;i++){
		scanf("%lld", &a[i]);
		a[i]+=a[i-1];
	}
	scanf("%d", &q);
	while(q--){
		int tag;
		scanf("%d", &tag);
		if(tag==1){
			int x, y, num;
			scanf("%d%d%d", &x, &y, &num);
			update(x, num);
			update(y+1, -num);
		}
		else {
			int x, y;
			scanf("%d%d", &x, &y);
			printf("%lld\n", query(y)-query(x-1));
		}
	}
}

