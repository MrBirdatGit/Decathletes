#include <bits/stdc++.h>
using namespace std;
char str[105];
int n;
int main(){
	scanf("%d%s", &n, str);
	int tmp=0;
	for(int i=0;i<=n;i++){
		if(i==n||str[i]=='0'){
			cout<<tmp;
			tmp=0;
		}
		else tmp++;
	}
	cout<<endl;
}

