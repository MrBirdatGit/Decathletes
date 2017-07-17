#include <bits/stdc++.h>
using namespace std;
int a[205000];
int b[205000];
int f[205000];
char s[205000][30];
int main(){
	int n, m;
	scanf("%d", &n);
	for(int i=1;i<=n;i++)scanf("%s", s[i]);
	scanf("%d", &m);
	for(int i=1;i<=m;i++)scanf("%d%d", &a[i], &b[i]);
	int st=1, pos=m;
	while(1){
		int to=-1;
		while(pos&&a[pos]!=st)pos--;
		if(!pos){
			printf("%s\n", s[st]);
			return 0;
		}
		else {
			printf("I_love_");
			st=b[pos--];
		}
	}
}

