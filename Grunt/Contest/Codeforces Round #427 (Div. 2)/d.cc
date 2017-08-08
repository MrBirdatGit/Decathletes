#include <bits/stdc++.h>
using namespace std;
char s[5050];
int dp[5050][5050];
int ans[5050];
int n;
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++){dp[i][i]=1;ans[1]++;}
	for(int i=1;i<n;i++)if(s[i]==s[i+1]){dp[i][i+1]=2;ans[2]++;}
	for(int len=3;len<=n;len++){
		for(int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			if(s[l]!=s[r]||dp[l+1][r-1]==0)continue;
			int lenp=len/2;
			int rp=l+lenp-1;
			dp[l][r]=dp[l][rp]+1;
			ans[dp[l][r]]++;
		}
	}
	for(int i=n-1;i>=1;i--)ans[i]+=ans[i+1];
	for(int i=1;i<=n;i++)printf("%d%c",ans[i],i==n?'\n':' ');
}
