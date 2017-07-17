#include <bits/stdc++.h>
using namespace std;
char str[205000];
int ans[205000];
char s[]="happiness";
int tot;
int main(){
	srand(14453266356);
	scanf("%s", str);
	tot=0;
	int n=strlen(str);
	for(int i=0;i<n;i++){
		bool ok=true;
		for(int j=0;j<=8;j++){
			if(str[i+j]!=s[j])ok=false;
		}
		if(ok)ans[++tot]=i;
	}
	int a=rand()%n+1;
	int b=rand()%n+1;
	while(b==a){
		b=rand()%n+1;
	}
	if(tot>2)printf("NO\n");
	else if(tot==2)printf("YES\n%d %d\n", ans[1]+1, ans[2]+2);
	else if(tot==1)printf("YES\n%d %d\n", ans[1]+1, ans[1]+2);
	else printf("YES\n%d %d\n", a, b);
}

