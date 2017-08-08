#include <bits/stdc++.h>
using namespace std;
int a[105000];
int n;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+1+n);
	bool fj=false,zj=false;
	int fjm,zjm;
	int sum=0;
	for(int i=1;i<=n;i++){
		if(a[i]<0){
			if(a[i]%2!=0){
				fj=true;
				fjm=a[i];
			}
		}
		else {
			if(a[i]%2!=0&&!zj){
				zj=true;
				zjm=a[i];
			}
			sum+=a[i];
		}
	}
	if(sum%2!=0)cout<<sum<<endl;
	else {
		if(!fj){
			cout<<sum-zjm<<endl;
		}
		else if(!zj){
			cout<<sum+fjm<<endl;
		}
		else {
			cout<<sum-min(-fjm,zjm)<<endl;
		}
	}
}
