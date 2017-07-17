#include <bits/stdc++.h>
using namespace std;
int main(){
	long long a, b, c, n, m;
	cin>>a>>b>>c>>n>>m;
	long long ans=a+b+c;
	if(a+c>n)ans=min(ans, n);
	if(b+c>m)ans=min(ans, m);
	cout<<ans<<endl;
}

