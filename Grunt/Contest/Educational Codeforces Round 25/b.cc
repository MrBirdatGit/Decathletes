#include <bits/stdc++.h>
using namespace std;
char g[11][11];
int cnt[3];
int main(){
	for(int i=1;i<=10;i++)scanf("%s", g[i]+1);
	bool ok=false;
	for(int i=1;i<=10;i++){
		for(int j=1;j<=10;j++){
			memset(cnt, 0, sizeof(cnt));
			for(int k=0;k<5;k++){
				cnt[0]+=(g[i][j+k]=='X');
				cnt[1]+=(g[i][j+k]=='O');
				cnt[2]+=(g[i][j+k]=='.');
			}
			if(cnt[0]==4&&cnt[2]==1)ok=true;

			memset(cnt, 0, sizeof(cnt));
			for(int k=0;k<5;k++){
				cnt[0]+=(g[i+k][j]=='X');
				cnt[1]+=(g[i+k][j]=='O');
				cnt[2]+=(g[i+k][j]=='.');
			}
			if(cnt[0]==4&&cnt[2]==1)ok=true;

			memset(cnt, 0, sizeof(cnt));
			for(int k=0;k<5;k++){
				cnt[0]+=(g[i+k][j+k]=='X');
				cnt[1]+=(g[i+k][j+k]=='O');
				cnt[2]+=(g[i+k][j+k]=='.');
			}
			if(cnt[0]==4&&cnt[2]==1)ok=true;

			if(i>=5){
				memset(cnt, 0, sizeof(cnt));
				for(int k=0;k<5;k++){
					cnt[0]+=(g[i-k][j+k]=='X');
					cnt[1]+=(g[i-k][j+k]=='O');
					cnt[2]+=(g[i-k][j+k]=='.');
				}
				if(cnt[0]==4&&cnt[2]==1)ok=true;
			}
		}
	}
	if(ok)cout<<"YES\n";
	else cout<<"NO\n";
}

