#include <bits/stdc++.h>
using namespace std;
int a[105000];
int dp[105000][400];
int bd;
int n,q;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}	
	bd=sqrt(n);
	for(int j=1;j<=bd;j++){
		for(int i=n;i>=1;i--){
			int to=i+a[i]+j;
			if(to>n)dp[i][j]=1;
			else dp[i][j]=dp[to][j]+1;
		}
	}
	cin>>q;
	while(q--){
		int p,k;
		cin>>p>>k;
		if(k<=bd)cout<<dp[p][k]<<endl;
		else {
			int cnt=0;
			while(p<=n){
				cnt++;
				p+=a[p]+k;
			}
			cout<<cnt<<endl;
		}
	}
}
