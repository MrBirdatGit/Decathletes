#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,k;
int a[205000];
int ma[205000][25];
int mi[205000][25];
int lo[205000];

bool check(int l,int r){
	int j=lo[r-l+1];
	return max(ma[l][j],ma[r-(1<<j)+1][j])-min(mi[l][j],mi[r-(1<<j)+1][j])<=k;
}

int main(){
	for(int i=1;i<=200000;i++)lo[i]=31-__builtin_clz(i);
	for(int i=1;i<=33;i++)printf("%d %d\n",i,lo[i]); 
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){scanf("%d",&a[i]);ma[i][0]=a[i];mi[i][0]=a[i];}
	for(int j=1;1<<j<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			ma[i][j]=max(ma[i][j-1],ma[i+1<<(j-1)][j-1]);
			mi[i][j]=min(mi[i][j-1],mi[i+1<<(j-1)][j-1]);
		}
	}
	ll ans=0;
	for(int i=1;i<=n;i++){
		int l=i,r=n;
		int tag=-1;
		while(l<=r){
			if(r-l<=1){
				if(check(i,r))tag=r;
				else tag=l;
				break;
			}
			int mid=l+r>>1;
			if(check(i,mid))l=mid;
			else r=mid;
		}
		ans+=tag-i+1;
	}
	printf("%lld\n",ans);
}
