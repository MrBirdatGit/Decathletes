//垃圾trie板题
//唯一难点在于复杂度估计
//毕竟跑满10*1000*1000*31在非cf上很容易挂
//垃圾曹主席, 这特么也算模拟？
#include <bits/stdc++.h>
using namespace std;
struct Trie{
	int ch[32050][2];
	int end[32050];
	int sz;
	int newnode(){
		ch[sz][0]=ch[sz][1]=-1;
		end[sz]=1;
		return sz++;
	}
	void init(){
		sz=0;
		newnode();
	}
	void insert(int num){
		int u=0;
		for(int i=30;i>=0;i--){
			int c=(num>>i)&1;
			if(ch[u][c]==-1)ch[u][c]=newnode();
			else end[ch[u][c]]++;
			u=ch[u][c];
		}
	}
	void del(int num){
		int u=0;
		for(int i=30;i>=0;i--){
			int c=(num>>i)&1;
			end[ch[u][c]]--;
			u=ch[u][c];
		}
	}
	int query(int num){
		int u=0;
		int ans=0;
		for(int i=30;i>=0;i--){
			int c=(num>>i)&1;
			if(ch[u][c^1]!=-1&&end[ch[u][c^1]]){
				ans|=(1<<i);
				u=ch[u][c^1];
			}
			else {
				u=ch[u][c];
			}
		}
		return ans;
	}
};

Trie trie;

int a[1050], n;

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		trie.init();
		scanf("%d", &n);
		for(int i=1;i<=n;i++){scanf("%d", &a[i]);trie.insert(a[i]);}
		int ans=0;
		for(int i=1;i<=n;i++){
			trie.del(a[i]);
			for(int j=i+1;j<=n;j++){
				trie.del(a[j]);
				ans=max(ans, trie.query(a[i]+a[j]));
				trie.insert(a[j]);
			}
			trie.insert(a[i]);
		}
		printf("%d\n", ans);
	}
}

