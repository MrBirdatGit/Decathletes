//给一个靠左的棋盘
//第i行有a[i]个格子
//问放k个不相攻击的车有多少种方法
//注意如果a[i][k]和a[j][k]之间有缺口也算互相攻击
//排序后就是垃圾dp了
//因为最多有250!种, 要用大整数
//并且避免MLE要用滚动数组
#include <bits/stdc++.h>
using namespace std;
struct num{
	int len;
	int a[1050];
	void init(){
		len=0;
		memset(a, 0, sizeof(a));
	}
	void build(int x){
		init();
		while(x){
			a[len++]=x%10;
			x/=10;
		}
	}
	void print(){
		if(len==0)printf("0\n");
		else {
			for(int i=len-1;i>=0;i--){
				printf("%d", a[i]);
			}
			printf("\n");
		}
	}
};

num add(num a, num b){
	num c;
	c.init();
	c.len=max(a.len, b.len);
	for(int i=0;i<c.len;i++)c.a[i]=a.a[i]+b.a[i];
	for(int i=0;i<c.len;i++){
		c.a[i+1]+=c.a[i]/10;
		c.a[i]%=10;
	}
	int tmp=c.len;
	while(c.a[tmp]){
		c.a[tmp+1]+=c.a[tmp]/10;
		c.a[tmp]%=10;
		tmp++;
	}
	c.len=tmp;
	return c;
}

num mul(num a, int b){
	for(int i=0;i<a.len;i++){
		a.a[i]*=b;
	}
	for(int i=0;i<a.len;i++){
		a.a[i+1]+=a.a[i]/10;
		a.a[i]%=10;
	}
	int tmp=a.len;
	while(a.a[tmp]){
		a.a[tmp+1]+=a.a[tmp]/10;
		a.a[tmp]%=10;
		tmp++;
	}
	a.len=tmp;
	return a;
}

int n, k;
int rec[255];
num dp[255];

int main(){
	scanf("%d%d", &n, &k);
	for(int i=1;i<=n;i++)scanf("%d", &rec[i]);
	sort(rec+1, rec+1+n);
	for(int i=0;i<=250;i++)dp[i].init();
	dp[0].build(1);
	for(int i=1;i<=n;i++){
		for(int j=rec[i]-1;j>=0;j--){
			dp[j+1]=add(dp[j+1], mul(dp[j], rec[i]-j));
		}
	}
	dp[k].print();
}

