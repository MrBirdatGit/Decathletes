#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=20500;
int s[maxn];
int sa[maxn], t[maxn], t2[maxn], c[maxn], n;
int Rank[maxn], height[maxn];
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

int main()
{
	n=8;
	s[8]=0;
	s[0]=s[1]=2;
	s[2]=s[3]=s[4]=s[5]=1;
	s[6]=s[7]=3;
	build_sa(200, n+1);
	geth(n+1);
	for(int i=0;i<=n;i++){
		printf("%d ", sa[i]);
	}
	printf("\n");
	for(int i=1;i<=n;i++){
		printf("%d ", height[i]);
	}
	printf("\n");

}

