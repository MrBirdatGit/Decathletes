#include <bits/stdc++.h>
using namespace std;
//double a[105000];
int add[]={10,99,998,9997,99996,999995,9999994,99999993,999999992,1000000000};
int main(){
	int n;
	while(~scanf("%d",&n)){
		int tag=0;
		for(int i=9;i>=0;i--)if(n<=add[i])tag=i;
		cout<<n+tag<<endl;
	}
}
