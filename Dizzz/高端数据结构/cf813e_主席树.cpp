#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
int rt[maxn],cnt[maxn*20],ls[maxn*20],rs[maxn*20],tot;
int k;
void bulid(int &x,int l,int r){
	x = ++tot;
	cnt[x] = 0;
	if(l == r) return;
	int m = (l+r)>>1;
	bulid(ls[x],l,m);
	bulid(rs[x],m+1,r);
}
void update(int last,int &x,int l,int r,int p){
	x = ++tot;
	ls[x] = ls[last];
	rs[x] = rs[last];
	cnt[x] = cnt[last]+1;
	if(l == r) return;
	int m = (l+r)>>1;
	if(p<=m) update(ls[last],ls[x],l,m,p);
	else update(rs[last],rs[x],m+1,r,p);
}
int query(int ll,int rr,int l,int r,int k){
	if(l == r){
		return cnt[rr] - cnt[ll];	
	}
	int m = (l+r)>>1;
	if(k <= m) return query(ls[ll],ls[rr],l,m,k);
	else return cnt[ls[rr]] - cnt[ls[ll]] + query(rs[ll],rs[rr],m+1,r,k);
}
int a[maxn],b[maxn],N;
map<int,int>mp;
vector<int>vec[maxn];
int main(){
	int n;
	scanf("%d%d",&n,&k);
	for(int i = 1;i<=n;i++){
		scanf("%d",a+i);
		if(mp[a[i]]== 0) mp[a[i]] = ++N;
		vec[mp[a[i]]].push_back(i);
	}	
	for(int i = 1;i<=N;i++){
		for(int j = 0;j<vec[i].size();j++){
			if(j < k) b[vec[i][j]] = 0;
			else b[vec[i][j]] = vec[i][j-k];
		}
	}
	bulid(rt[0],0,n);
	for(int i = 1;i<=n;i++){
		update(rt[i-1],rt[i],0,n,b[i]);
	}
	int q;
	scanf("%d",&q);
	int last = 0,x,y,l,r;
	while(q--){
		scanf("%d%d",&x,&y);
		l = (x+last)%n + 1;
		r = (y+last)%n + 1;
		if(l>r) swap(l,r);
		printf("%d\n",last=query(rt[l-1],rt[r],0,n,l-1));
	}
}
