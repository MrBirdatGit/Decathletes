#include <bits/stdc++.h>
using namespace std;
int n,k,tot=0;
int ans[100];
int main(){
	cin>>n>>k;
	for(int i=2;i*i<=n;i++){
		if(n%i==0){
			while(n%i==0){
				ans[++tot]=i;
				n/=i;
			}
		}
	}
	if(n!=1)ans[++tot]=n;
	if(tot<k)printf("-1\n");
	else {
		for(int i=tot;i>k;i--){
			ans[i-1]*=ans[i];
		}
		for(int i=1;i<=k;i++){
			printf("%d%c",ans[i],i==k?'\n':' '); 
		}
	}
}
