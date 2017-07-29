#include<bits/stdc++.h>
using namespace std;
int a[1010];
int main(){
	int n;
	while(~scanf("%d", &n)){
		int sum = 0;
		for(int i = 1;i<=n;i++)
			scanf("%d", a+i);
		sort(a+1, a+n+1);
		int ans = 0;
		for(int i = 1;i<=n;i++){
			if(a[i] > sum + 1){
				ans = sum+1;
				break;
			}
			sum += a[i];
		}
		if(ans != 0)
			printf("%d\n", ans);
		else
			printf("%d\n", sum+1);
	}
}

