//好题
//归结于求使得sigma(x*[ai/x]-ai)<=k的最大x值([]是上取整)
//移项后得x*sigma([ai/x])<=R
//这里要考虑到[a/x]只有sqrt(a)个答案，构成sqrt(a)个相同的区间
//那sigma([ai/x])则是nsqrt(a)个相同的区间
//那么维护出每个区间的左右端点就行了
//那么如何维护出这些区间呢？
//首先考虑只需要知道右端点即可
//引入一个结论:使得n/i==n/x的最大值x=n/(n/i);
//这个结论ZQC大神在知乎上有证明 https://zhuanlan.zhihu.com/p/26020672
//考虑到[ai/x]=(ai-1)/x+1, 那其实ai的上取整右端点和ai-1的下取整右端点是一样的
//取出所有右端点之后在每个线段上找最大值即可
//总复杂度O(n*n*sqrt(ai)*log(nsqrt(ai)))
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll k, a[105];
set<ll>s;
ll sum;
int main(){
	scanf("%d%lld", &n, &k);
	sum=k;
	for(int i=1;i<=n;i++){
		scanf("%lld", &a[i]);
		sum+=a[i]--;
	}
	for(int i=1;i<=n;i++){
		for(ll l=1;l<=a[i];){
			ll r=a[i]/(a[i]/l);
			s.insert(r);
			l=r+1;
		}
	}
	s.insert(1LL<<40);
	ll ans=1;
	ll last=1;
	for(auto it=s.begin();it!=s.end();it++){
		ll tmp=*it;
		ll mul=0;
		for(int i=1;i<=n;i++){
			mul+=a[i]/tmp+1;
		}
		ll x=sum/mul;
		if(x>=last)ans=min(tmp, x);
		last=tmp+1;
	}
	printf("%lld\n", ans);
}

