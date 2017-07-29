#include <bits/stdc++.h>
using namespace std;
const int inf=10000;
int n;
char s[105];
int num[105];
int dp[105][105][2];
int cmp[105][105][105];
int main()
{
	while(~scanf("%d", &n)){
		scanf("%s", s+1);
		for(int i=1;i<=n;i++)num[i]=s[i]-'0';
		memset(cmp, 0, sizeof(cmp));
		//printf("sb\n");
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				int h=j+1;
				for(int k=j;k>=i;k--)if(num[k])h=k;
				//if(i==2&&j==3)printf("sb %d\n", h);
				int c=0;
				for(int k=1;i-k>0;k++){
					/* cout<<k<<endl; */
					int wb;
					if(k>j-i+1)wb=0;
					else wb=num[j-k+1];
					if(num[i-k]<wb){
						cmp[i][j][k]=-1;
						c=-1;
					}
					else if(num[i-k]==wb){
						if(j-h+1>k){
							cmp[i][j][k]=-1;
						}
						else if(j-h+1==k){
							cmp[i][j][k]=c;
						}
						else {
							cmp[i][j][k]=c;
						}
					}
					else{
						if(j-h+1>k){
							cmp[i][j][k]=-1;
							c=1;
						}
						else if(j-h+1==k){
							cmp[i][j][k]=1;
							c=1;
						}
						else {
							cmp[i][j][k]=1;
							c=1;
						}
					}
				}
			}
		}
		/*int i, j, k;
		  while(1){
		  scanf("%d%d%d", &i, &j, &k);
		  printf("%d\n", cmp[i][j][k]);
		}*/
		for(int i=0;i<=n;i++){
			for(int j=0;j<=n;j++){
				for(int k=0;k<2;k++){
					dp[i][j][k]=-inf;
				}
			}
		}
		for(int i=1;i<=n;i++){
			dp[i][i][0]=0;
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<i;j++){
				int p=i-j;
				for(int k=1;k<=p;k++){
					if(cmp[p+1][i][k]>0){
						dp[i][j][0]=max(dp[i][j][0], dp[p][k][1]+1);
					}
					if(cmp[p+1][i][k]<0){
						dp[i][j][1]=max(dp[i][j][1], dp[p][k][0]+1);
					}
				}
			}
		}
		/*for(int i=1;i<=n;i++){
			for(int j=1;j<=i;j++){
				printf("%d %d %d %d\n", i, j, dp[i][j][0], dp[i][j][1]);
			}
		}*/
		int ans=0;
		for(int i=1;i<=n;i++){
			ans=max(ans, dp[n][i][0]);
			ans=max(ans, dp[n][i][1]);
		}
		printf("%d\n", ans);
	}
}

