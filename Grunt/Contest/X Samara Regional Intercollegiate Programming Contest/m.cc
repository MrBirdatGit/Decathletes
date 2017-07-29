#include <bits/stdc++.h>
using namespace std;
int rec[205000];
int n;
int tot=0;
int a[205000];
int b[205000];
int main(){
	scanf("%d", &n);
	for(int i=1;i<=n;i++){
		scanf("%d", &rec[i]);
	}
	int kill=0;
	int bekill=n;
	for(int i=1;i<=n;i++)if(rec[i])kill=i;
	while(kill){
		if(kill==bekill)return 0*printf("NO\n");
		++tot;
		a[tot]=kill;
		b[tot]=bekill;
		bekill--;
		rec[kill]--;
		if(rec[kill]==0)kill--;
	}
	printf("YES\n");
	for(int i=1;i<=tot;i++)printf("%d %d\n", a[i], b[i]);
}

