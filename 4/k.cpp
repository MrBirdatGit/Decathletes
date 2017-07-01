#include <bits/stdc++.h>
using namespace std;
struct node{
	int a[24];
};
int b[24]={0, 1, 2, 3, 4, 5, 10, 11, 6, 7, 12, 13, 8, 9, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
int p[6][24]=
{
	20, 1, 22, 3, 10, 4, 0, 7, 8, 9, 11, 5, 2, 13, 14, 15, 6, 17, 12, 19, 16, 21, 18, 23,
	0, 1, 8, 14, 4, 3, 7, 13, 17, 9, 10, 2, 6, 12, 16, 15, 5, 11, 18, 19, 20, 21, 22, 23,
	1, 3, 0, 2, 23, 22, 4, 5, 6, 7, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 9, 8,
	6, 1, 12, 3, 5, 11, 16, 7, 8, 9, 4, 10, 18, 13, 14, 15, 20, 17, 22, 19, 0, 21, 2, 23,
	2, 0, 3, 1, 6, 7, 8, 9, 23, 22, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 5, 4,
	0, 1, 11, 5, 4, 16, 12, 6, 2, 9, 10, 17, 13, 7, 3, 15, 14, 8, 18, 19, 20, 21, 22, 23
};
int cal(node a){
	int ans=0;
	for(int i=0;i<6;i++){
		bool ok=true;
		for(int j=0;j<4;j++){
			if(a.a[b[j+i*4]]!=a.a[b[i*4]])ok=false;
		}
		ans+=(ok==true);
	}
	return ans;
}

int n;
int ans;
node trans;
void dfs(node a, int flor){
	ans=max(ans, cal(a));
	if(flor>n){
		return;
	}
	for(int i=0;i<6;i++){
		for(int j=0;j<24;j++){
			trans.a[p[i][j]]=a.a[j];
		}
		dfs(trans, flor+1);
	}
}
int main()
{
	while(~scanf("%d", &n)){
		node st;
		for(int i=0;i<24;i++){
			scanf("%d", &st.a[i]);
		}
		ans=0;
		dfs(st, 1);
		printf("%d\n", ans);
	}
}