//几个地方题意理解错了，浪费了很多时间：
//字符集是256的
//每种字符只统计一次
//理清'='的作用
//要读清题意啊，尤其是这种题面很长的
#include <bits/stdc++.h>
using namespace std;
struct Trie{
	int ch[40000][256];
	int fail[40000];
	int end[40000];
	int sz;
	int newnode(){
		for(int i=0;i<256;i++)ch[sz][i]=-1;
		end[sz]=-1;
		return sz++;
	}
	void init(){
		sz=0;
		newnode();
	}
	void insert(unsigned char s[], int len, int id){
		int u=0;
		for(int i=0;i<len;i++){
			if(ch[u][s[i]]==-1){
				ch[u][s[i]]=newnode();
			}
			u=ch[u][s[i]];
		}
		end[u]=id;
	}
	void build(){
		queue<int>q;
		fail[0]=0;
		for(int i=0;i<256;i++){
			if(ch[0][i]==-1)ch[0][i]=0;
			else {
				fail[ch[0][i]]=0;
				q.push(ch[0][i]);
			}
		}
		while(!q.empty()){
			int u=q.front();
			q.pop();
			for(int i=0;i<256;i++){
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
	bool vis[600];
	int query(unsigned char s[], int len, int n){
		memset(vis, false, sizeof(vis));
		int u=0;
		for(int i=0;i<len;i++){
			u=ch[u][s[i]];
			int tmp=u;
			while(tmp){
				if(end[tmp]!=-1)vis[end[tmp]]=true;
				tmp=fail[tmp];
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++)ans+=(vis[i]==true);
		return ans;
	}
};

int idx(int c){
	if(c>='A'&&c<='Z')return c-'A';
	if(c>='a'&&c<='z')return c-'a'+26;
	if(c>='0'&&c<='9')return c-'0'+52;
	if(c=='+')return 62;
	if(c=='/')return 63;
	return -1;
}

Trie T;
int n, m;
char s0[3000];
int bi[20000];
int totb;
unsigned char s[3000];
int tots;

void trans1(){
	totb=0;
	int len=strlen(s0);
	for(int i=0;i<len;i++){
		if(s0[i]=='='){
			--totb;
			--totb;
		}
		else {
			int num=idx(s0[i]);
			for(int i=1;i<=6;i++){
				bi[totb+i]=(num>>(6-i))&1;
			}
			totb+=6;
		}
	}
}

void trans2(){
	memset(s, 0, sizeof(s));
	tots=0;
	for(int i=1;i<=totb;i+=8){
		int num=0;
		for(int j=0;j<8;j++){
			num<<=1;
			num+=bi[i+j];
		}
		s[tots++]=num;
	}
}

int main()
{
	while(~scanf("%d", &n)){
		T.init();
		for(int i=1;i<=n;i++){
			scanf("%s", s0);
			trans1();
			trans2();
			T.insert(s, tots, i);
		}
		T.build();
		scanf("%d", &m);
		for(int i=1;i<=m;i++){
			scanf("%s", s0);
			trans1();
			trans2();
			printf("%d\n", T.query(s, tots, n));
		}
		printf("\n");
	}
}

