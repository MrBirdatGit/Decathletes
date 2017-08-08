#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
const ll mod=1000000000039;
const ll mod1=1e9+7;
int n,m;
char s[5050][5050];
int cnt[5050];
ll h[5050];
ll h1[5050];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		h[i]=0;
		h1[i]=0;
		for(int j=1;j<=m;j++){
			h[i]<<=1;
			h1[i]<<=1;
			h[i]+=s[i][j]-'0';
			h1[i]+=s[i][j]-'0';
			h[i]%=mod;
			h1[i]%=mod1;
			if(s[i][j]=='1')cnt[i]++;
		}
	}
	int M=0;
	int id=0;
	for(int i=1;i<=n;i++){
		if(cnt[i]>=8&&cnt[i]<=15){
			int tmp=0;
			for(int j=1;j<=n;j++)if(h[i]==h[j]&&h1[i]==h1[j])tmp++;
			if(tmp>M){
				M=tmp;
				id=i;
			}
		}
	}
	if(id==0){
		for(int i=1;i<=8;i++)printf("1");
		for(int i=9;i<=m;i++)printf("0");
		printf("\n");
	}
	else {
		printf("%s\n",s[id]+1);
	}
}
