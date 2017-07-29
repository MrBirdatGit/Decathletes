#include <bits/stdc++.h>
using namespace std;
char s[105000];
char stk[105000];
int top=0;
char u[105000];
int tot=0;
char m[105000];
int main(){
	cin>>s;
	int len=strlen(s);
	m[len-1]=s[len-1];
	for(int i=len-2;i>=0;i--){
		m[i]=min(s[i],m[i+1]);
	}
	for(int i=0;s[i];i++){
		while(top&&stk[top]<=m[i])u[tot++]=stk[top--];
		stk[++top]=s[i];
	}
	while(top)u[tot++]=stk[top--];
	cout<<u<<endl;
}
