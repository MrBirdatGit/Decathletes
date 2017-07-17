#include <bits/stdc++.h>
using namespace std;
int n, k;
int main(){
	while(~scanf("%d%d", &n, &k)){
		int tmp=0;
		for(int i=1;i<=n;i++){
			int x;
			scanf("%d", &x);
			tmp=__gcd(tmp, x);
		}
		if(k%tmp==0)printf("YES\n");
		else printf("NO\n");
	}
}

