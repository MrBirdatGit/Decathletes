//bzoj1010
//决策单调性
//
//P教授要去看奥运，但是他舍不下他的玩具，于是他决定把所有的玩具运到北京。他使用自己的压缩器进行压缩，其可以将任意物品变成一堆，再放到一种特殊的一维容器中。P教授有编号为1…N的N件玩具，第i件玩具经过压缩后变成一维长度为Ci.为了方便整理，P教授要求在一个一维容器中的玩具编号是连续的。同时如果一个一维容器中有多个玩具，那么两件玩具之间要加入一个单位长度的填充物，形式地说如果将第i件玩具到第j个玩具放到一个容器中，那么容器的长度将为 x=j-i+Sigma(Ck) i<=K<=j 制作容器的费用与容器的长度有关，根据教授研究，如果容器长度为x,其制作费用为(X-L)^2.其中L是一个常量。P教授不关心容器的数目，他可以制作出任意长度的容器，甚至超过L。但他希望费用最小.
//
//input
//5 4
//3
//4
//2
//1
//4
//
//output
//1
//
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=50005;
ll a[maxn], s[maxn], dp[maxn], l;
int n;
struct node{
	int l, r, p;
}q[maxn];
ll cal(int j, int i){
	return dp[j]+(s[i]-s[j]+i-j-1-l)*(s[i]-s[j]+i-j-1-l);
}
int bisearch(node a, int i){
	int l=a.l, r=a.r+1, tag=0;//这里我的二分默认在l到r之间有答案的, 而实际上有可能a.r并不满足, 所以把区间右端点+1
	while(l<=r){
		if(r-l<=1){
			if(cal(i, l)<cal(a.p, l))tag=l;
			else tag=r;
			break;
		}
		int mid=l+r>>1;
		if(cal(i, mid)<cal(a.p, mid))r=mid;
		else l=mid;
	}
	return tag;
}
void solve(){
	int head=1, tail=0;
	q[++tail]=(node){0, n, 0};
	for(int i=1;i<=n;i++){
		if(i>q[head].r)head++;
		dp[i]=cal(q[head].p, i);
		/*for(int i=head;i<=tail;i++){
				printf("node %d %d %d\n", q[i].l, q[i].r, q[i].p);
			}
		cout<<i<<' '<<q[head].p<<' '<<dp[i]<<endl;*/
		if(head>tail||cal(i, n)<cal(q[tail].p, n)){
			while(head<=tail&&cal(i, q[tail].l)<cal(q[tail].p, q[tail].l))tail--;
			if(head<=tail){
				int t=bisearch(q[tail], i);
				q[tail].r=t-1;
				q[++tail]=(node){t, n, i};
			}
			else q[++tail]=(node){i, n, i};
		}
	}
}
int main(){
	scanf("%d%lld", &n, &l);
	for(ll i=1;i<=n;i++){
		scanf("%lld", &a[i]);
		s[i]=s[i-1]+a[i];
	}
	solve();
	printf("%lld\n", dp[n]);
}

