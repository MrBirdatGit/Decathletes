#include <bits/stdc++.h>
using namespace std;
int main(){
	int s,v1,v2,t1,t2;
	cin>>s>>v1>>v2>>t1>>t2;
	int a=s*v1+2*t1;
	int b=s*v2+2*t2;
	if(a<b)cout<<"First\n";
	else if(a>b)cout<<"Second\n";
	else cout<<"Friendship\n";
}
