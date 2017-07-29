#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int>P;
typedef long long ll;
const int maxn = 250100;
const ll mod = 1e9+7;
int a[maxn],b[maxn],cnt[maxn];
int main(){
	int n;
	while(~scanf("%d",&n)){
		priority_queue<P,vector<P>,less<P> >que;
		for(int i = 1;i<=n;i++){
			scanf("%d",a+i);
			que.push(make_pair(a[i]-i,i));
		}
		for(int i = 1;i<=n;i++){
			scanf("%d",b+i);
		}
		sort(b+1,b+n+1);
		ll ans = 0;
		for(int i = 1;i<=n;i++){
			P p = que.top();
			while(p.second<b[i]){
				que.pop();
				p = que.top();
			}
			//cout<<p.first<<' '<<p.second<<' '<<b[i]<<endl;
			que.push(make_pair(p.first-i-n,i+n));
			ans = (ans + p.first)%mod;
		}	
		printf("%lld\n",ans);
	}
}
