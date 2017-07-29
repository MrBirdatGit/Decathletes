#include <bits/stdc++.h>
using namespace std;
int v[105000];
int l[105000];
int r[105000];
bool used[105000];
map<int,int>mp;
int n,rt;
int opp=0;
void dfs(int u,int le,int ri){
	if(v[u]>=le&&v[u]<=ri){
		opp+=mp[v[u]];
		mp[v[u]]=0;
	}
	if(l[u]!=-1)dfs(l[u],le,min(ri,v[u]));
	if(r[u]!=-1)dfs(r[u],max(le,v[u]),ri);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>v[i]>>l[i]>>r[i];
		used[l[i]]=true,used[r[i]]=true;
		mp[v[i]]++;
	}
	for(int i=1;i<=n;i++)if(!used[i])rt=i;
	dfs(rt,0,1e9+7);
	cout<<n-opp<<endl;
}
