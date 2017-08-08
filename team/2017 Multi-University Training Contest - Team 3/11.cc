#include <bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	int cnt=0;
	for(int i=1;i<=t;i++){
		int a;
		cin>>a;
		if(a<=35)cnt++;
	}
	cout<<cnt<<endl;
}
