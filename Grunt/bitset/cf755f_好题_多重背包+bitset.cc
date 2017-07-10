//好题
//问题归结为:
//能否将总重量不大于1e6的砝码分成两堆, 其中一堆重量为k
//用多重背包的按位拆分+bitset可以达到o(n*sigma(logk)/64)
//而由于sigma(k)=n, 最坏情况sigma(logk)~sqrt(n)
#include <bits/stdc++.h>
using namespace std;

int a[1050000];
bool vis[1050000];
int cnt[1050000];
bitset<1050000>b;
int n, k;
int ma=0, mi, bonus=0;

int main(){
	scanf("%d%d", &n, &k);
	for(int i=1;i<=n;i++)scanf("%d", &a[i]);
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		int tmp=i;
		int len=0;
		while(!vis[tmp]){
			vis[tmp]=true;
			len++;
			tmp=a[tmp];
		}
		cnt[len]++;
		bonus+=len/2;
	}
	ma=min(n, k+min(bonus, k));
	b[0]=1;
	for(int i=1;i<=n;i++){
		if(!cnt[i])continue;
		int k=1;
		while(k<cnt[i]){
			b|=b<<k*i;
			cnt[i]-=k;
			k<<=1;
		}
		b|=b<<cnt[i]*i;
	}
	if(b[k])mi=k;
	else mi=k+1;
	printf("%d %d\n", mi, ma);
}

