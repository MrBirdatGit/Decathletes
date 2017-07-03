#include <bits/stdc++.h>
using namespace std;
struct Trie{
	int ch[50500][27];
	int fail[50500];
	int end[50500];
	int sz;
	int newnode(){
		for(int i=0;i<27;i++)ch[sz][i]=-1;
		end[sz]=-1;
		return sz++;
	}
	void init(){
		sz=0;
		newnode();
	}
	int idx(int c){
		if(c>='A'&&c<='Z')return c-'A';
		return 26;
	}
	void insert(char s[], int id){
		int len=strlen(s);
		int u=0;
		for(int i=0;i<len;i++){
			int c=idx(s[i]);
			if(ch[u][c]==-1){
				ch[u][c]=newnode();
			}
			u=ch[u][c];
		}
		end[u]=id;
	}
	void build(){
		queue<int>q;
		fail[0]=0;
		for(int i=0;i<27;i++){
			if(ch[0][i]==-1)ch[0][i]=0;
			else {
				fail[ch[0][i]]=0;
				q.push(ch[0][i]);
			}
		}
		while(!q.empty()){
			int u=q.front();
			q.pop();
			for(int i=0;i<27;i++){
				if(ch[u][i]==-1){
					ch[u][i]=ch[fail[u]][i];
				}
				else {
					fail[ch[u][i]]=ch[fail[u]][i];
					q.push(ch[u][i]);
				}
			}
		}
	}
};

Trie T;
char s[1050][55];
char str[2050000];
int cnt[1050];
int n;

int main()
{
	while(~scanf("%d", &n)){
		memset(cnt, 0, sizeof(cnt));
		T.init();
		for(int i=1;i<=n;i++){
			scanf("%s", s[i]);
			T.insert(s[i], i);
		}
		T.build();
		scanf("%s", str);
		int len=strlen(str);
		int u=0;
		for(int i=0;i<len;i++){
			int c=T.idx(str[i]);
			u=T.ch[u][c];
			int tmp=u;
			while(tmp){
				if(T.end[tmp]!=-1){
					cnt[T.end[tmp]]++;
				}
				tmp=T.fail[tmp];
			}
		}
		for(int i=1;i<=n;i++){
			if(cnt[i]){
				printf("%s: %d\n", s[i], cnt[i]);
			}
		}
	}
}

