#include <bits/stdc++.h>
using namespace std;
char str[105000];
int k;
int main(){
	cin>>k>>str;
	int len=strlen(str);
	int sum=0;
	sort(str,str+len);
	for(int i=0;i<len;i++)sum+=str[i]-'0';
	int cnt=0;
	for(int i=0;i<len;i++){
		if(sum>=k)break;
		sum+='9'-str[i];
		cnt++;
	}
	cout<<cnt<<endl;
}
