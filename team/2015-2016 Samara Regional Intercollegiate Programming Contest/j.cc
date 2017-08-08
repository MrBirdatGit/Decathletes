#include<bits/stdc++.h>
using namespace std;

int d[100005],n;
int main()
{
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%d",&d[i]);
	sort(d,d+n);
	int ans=n-1;
	while(ans>=0 && d[ans]>ans) ans--;
	printf("%d\n",ans+1);
	return 0;
}
