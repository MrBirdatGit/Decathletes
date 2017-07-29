#include <bits/stdc++.h>
using namespace std;
int n,m,p;
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&m,&p);
		int num=n*m-1;
		int rev=0;
		while(num>p){
			long long term=(num-1)/p+1;
			long long add=(p-1)*term*(term-1)/2;
			add%=2;
			rev=(rev+add)%2;
			num-=term;
		}
		if(rev)printf("NO\n");
		else printf("YES\n");
	}
}
