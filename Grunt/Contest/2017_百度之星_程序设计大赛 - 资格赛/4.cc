#include <bits/stdc++.h>
using namespace std;
const int INF=1e9+7;

struct node {
	int v;
	int sum;
	int tag;
	void init(){
		v=0;
		sum=INF;
		tag=0;
	}
};

bool operator<(const node& a,const node& b){
	if(a.v==b.v)return a.sum>b.sum;
	return a.v<b.v;
} 

int b,n;
int v[105];
int c[105];
node dp[1050][1050];
int id[105];
node ans;
int tot;

int main(){
	int T;
	scanf("%d",&T);
	for(int tt=1;tt<=T;tt++){
		scanf("%d%d",&b,&n);
		for(int i=1;i<=n;i++){
			scanf("%d%d",&v[i],&c[i]);
		}
		dp[0][0]=(node){0,0,0};
		for(int i=1;i<=b;i++)dp[0][i].init();
		for(int i=1;i<=n;i++){
			for(int j=b;j>=0;j--){
				dp[i][j]=dp[i-1][j];
				if(j<c[i])continue;
				node tmp=(node){dp[i-1][j-c[i]].v+v[i],dp[i-1][j-c[i]].sum+i,i};
				if(dp[i][j]<tmp)dp[i][j]=tmp;
			}
		}
		tot=0;
		ans.init();
		int cost=0;
		for(int i=b;i>=0;i--)if(ans<dp[n][i]){ans=dp[n][i];cost=i;}
		printf("Case #%d:\n%d %d\n",tt,ans.v,cost);
		for(int i=n,cm=b;i>=1;i--){
			node tmp;
			tmp.init();
			int cost=0;
			for(int j=cm;j>=0;j--){
				if(tmp<dp[i][j]){tmp=dp[i][j];cost=j;}
			}
			if(dp[i][cost].tag==i){
				id[++tot]=i;
				cm=cost-c[i];
			}
		}
		for(int i=tot;i>=1;i--)printf("%d%c",id[i],i==1?'\n':' ');
	}
}
