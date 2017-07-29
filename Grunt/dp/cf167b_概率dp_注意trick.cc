//有很多比赛, 每场送包或奖品，包的容量是a[i], 可以装a[i]个奖品
//每场比赛夺冠概率已知为p[i]
//问有多少概率达到目标夺冠次数并能带回所有奖品
//比较水的概率dp
//但是要注意两个trick:
//一是参赛顺序可以自己调整, 所以要贪心地先参加送包的比赛
//二是k可能大于n
#include <bits/stdc++.h>
using namespace std;
double dp[205][205][205];
struct node{
	int p, a;
}rec[205];
bool cmp(node a, node b){
	return a.a>b.a;
}
int n, l, k;
int main(){
	scanf("%d%d%d", &n, &l, &k);
	k=min(k,n);//注意trick
	for(int i=1;i<=n;i++)scanf("%d", &rec[i].p);
	for(int i=1;i<=n;i++)scanf("%d", &rec[i].a);
	sort(rec+1, rec+1+n, cmp);
	memset(dp, 0, sizeof(dp));
	dp[0][k][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<=n;k++){
				if(rec[i].a==-1){
					if(j>0){
						dp[i][j-1][k+1]+=dp[i-1][j][k]*rec[i].p/100;
						dp[i][j][k]+=dp[i-1][j][k]*(100-rec[i].p)/100;
					}
					else {
						dp[i][j][k]+=dp[i-1][j][k]*(100-rec[i].p)/100;
					}
				}
				else {
					int to=min(n, j+rec[i].a);
					dp[i][to][k+1]+=dp[i-1][j][k]*rec[i].p/100;
					dp[i][j][k]+=dp[i-1][j][k]*(100-rec[i].p)/100;
				}
			}
		}
	}
	double ans=0;
	for(int j=0;j<=n;j++){
		for(int k=0;k<=n;k++){
			if(k>=l)ans+=dp[n][j][k];
		}
	}
	printf("%.8f\n", ans);
}

