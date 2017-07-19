#include <bits/stdc++.h>
using namespace std;
int dp[8050];
char str[8050];
int f[8050];
int num[10500];
int main(){
	for(int i=1;i<10;i++)num[i]=1;
	for(int i=10;i<100;i++)num[i]=2;
	for(int i=100;i<1000;i++)num[i]=3;
	for(int i=1000;i<10000;i++)num[i]=4;

	scanf("%s", str+1);
	int n=strlen(str+1);
	dp[0]=0;
	for(int i=1;i<=n;i++)dp[i]=10000;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			if(j==1){
				f[j]=0;
			}
			else{
				int k=f[j-1];
				while(k&&str[i-k]!=str[i-j+1]){
					k=f[k];
				}
				if(str[i-k]==str[i-j+1])k++;
				f[j]=k;
			}

			int l=j;
			int loop=l-f[j];
			if(l%loop==0){
				dp[i]=min(dp[i], dp[i-j]+loop+num[l/loop]);
			}
			else {
				dp[i]=min(dp[i], dp[i-j]+l+num[1]);
			}
		}
	}
	printf("%d\n", dp[n]);
}

