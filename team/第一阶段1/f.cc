#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int maxn=405000;
char str[maxn];
int s[maxn];
int id[maxn];
int sa[maxn], t[maxn], t2[maxn], c[maxn], n, tim;
int Rank[maxn], height[maxn];
int f[maxn][21];
void build_sa(int m, int n){
	int i, *x=t, *y=t2;
	for(i=0;i<m;i++)c[i]=0;
	for(i=0;i<n;i++)c[x[i]=s[i]]++;
	for(i=1;i<m;i++)c[i]+=c[i-1];
	for(i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
	for(int k=1;k<=n;k<<=1){
		int p=0;
		for(i=n-k;i<n;i++)y[p++]=i;
		for(i=0;i<n;i++)if(sa[i]>=k)y[p++]=sa[i]-k;
		for(i=0;i<m;i++)c[i]=0;
		for(i=0;i<n;i++)c[x[y[i]]]++;
		for(i=1;i<m;i++)c[i]+=c[i-1];
		for(i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
		swap(x, y);
		p=1;x[sa[0]]=0;
		for(i=1;i<n;i++)
			x[sa[i]]=y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
		if(p>=n)break;
		m=p;
	}
}
void geth(int n){
	int i, j, k=0;
	for(i=0;i<n;i++)Rank[sa[i]]=i;
	for(i=0;i<n;i++){
		if(k)k--;
		if(Rank[i]==0)break;
		j=sa[Rank[i]-1];
		while(s[i+k]==s[j+k])k++;
		height[Rank[i]]=k;
	}
}
bool check(int mid, int n){
	int i;
	int st=0;
	for(i=1;i<n;i++){
		if(height[i]<mid){
			if(i-st>=tim)return true;
			st=i;
		}
	}
	if(n-st>=tim)return true;
	return false;
}
bool cmp(int x, int y){
	return s[x]<s[y];
}

int query(int l, int r){
	int p=31-__builtin_clz(r-l+1);
	return min(f[l][p], f[r-(1<<p)+1][p]);
}

int ff(int num){
	if(num==0)return 1;
	int ans=0;
	while(num){
		ans++;
		num/=10;
	}
	return ans;
}

int main()
{
	while(~scanf("%s", str)){
		n=strlen(str);
		for(int i=0;i<n;i++)s[i]=str[i]-'a'+1;
		s[n++]=0;
		build_sa(30, n);
		geth(n);
		for(int i=0;i<n;i++)f[i][0]=height[i];
		//for(int i=0;i<n;i++)cout<<"h"<<i<<"="<<height[i]<<endl;
		for(int j=1;j<=20;j++){
			for(int i=0;i+(1<<j)-1<n;i++){
				f[i][j]=min(f[i][j-1], f[i+(1<<(j-1))][j-1]);
			}
		}
		int m;
		scanf("%d", &m);
		long long il=0, ol=0;
		int xt=0, yt=0;
		for(int i=1;i<=m;i++){
			int x, y;
			scanf("%d%d", &x, &y);
			il+=(y-x+1);
			ol+=2;
			if(x!=xt){
				int xr=Rank[x], xtr=Rank[xt];
				if(xr>xtr)swap(xr, xtr);
				int p=query(xr+1, xtr);
				p=min(y-x, p);
				p=min(yt-xt, p);
				ol+=ff(p);
				ol+=y-x-p;
			}
			else {
				int len=min(y, yt)-xt;
				ol+=ff(len);
				if(y>yt)ol+=y-yt;
			}
			xt=x;yt=y;
		}
		printf("%lld %lld\n", il, ol);
	}
}

