//二维树状数组板题
//单点插入区间查询
#include <bits/stdc++.h>
using namespace std;

bool vis[1050][1050];
int c[1050][1050];
int q;

int lowbit(int x){
	return x&(-x);
}

void update(int x, int y, int num){
	for(int i=x;i<=1001;i+=lowbit(i)){
		for(int j=y;j<=1001;j+=lowbit(j)){
			c[i][j]+=num;
		}
	}
}

int que(int x, int y){
	int ans=0;
	for(int i=x;i>0;i-=lowbit(i)){
		for(int j=y;j>0;j-=lowbit(j)){
			ans+=c[i][j];
		}
	}
	return ans;
}

int main(){
	memset(vis, false, sizeof(vis));
	memset(c, 0, sizeof(c));
	scanf("%d", &q);
	while(q--){
		char str[3];
		scanf("%s", str);
		if(str[0]=='B'){
			int x, y;
			scanf("%d%d", &x, &y);
			x++, y++;
			if(vis[x][y])continue;
			vis[x][y]=true;
			update(x, y, 1);
		}
		else if(str[0]=='D'){
			int x, y;
			scanf("%d%d", &x, &y);
			x++, y++;
			if(!vis[x][y])continue;
			vis[x][y]=false;
			update(x, y, -1);
		}
		else if(str[0]=='Q'){
			int xl, xr, yl, yr;
			scanf("%d%d%d%d", &xl, &xr, &yl, &yr);
			xl++, xr++, yl++, yr++;
			if(xl>xr)swap(xl, xr);//这里坑了，要注意trick啊
			if(yl>yr)swap(yl, yr);//
			int ans=que(xr, yr)-que(xr, yl-1)-que(xl-1, yr)+que(xl-1, yl-1);
			printf("%d\n", ans);
		}
	}
}

