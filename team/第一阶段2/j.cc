#include <bits/stdc++.h>
using namespace std;
const int INF=1e9;
char s[35][35];
int n;

struct node{
	int win;
	int mys;
	int ops;
};

bool operator==(const node&a, const node& b){
	return a.win==b.win&&a.mys==b.mys&&a.ops==b.ops;
}

bool operator<(const node&a, const node& b){
	if(a.win!=b.win)return a.win<b.win;
	if(a.ops!=b.ops)return a.ops>b.ops;
	return a.mys<b.mys;
}

map<string, set<int> >mst;
map<string, int>mp;
map<string, node>ans;

node dfs(string str){
	if(ans.find(str)!=ans.end())return ans[str];
	node M=(node){1, INF, 0};
	for(int i=0;i<26;i++){
		char p=i+'a';
		string add="";
		add+=p;
		string to1=add+str;
		if(mp.find(to1)!=mp.end()){
			node rev1=dfs(to1);
			if(rev1<M)M=rev1;
		}
		string to2=str+add;
		if(mp.find(to2)!=mp.end()){
			node rev2=dfs(to2);
			if(rev2<M)M=rev2;
		}
	}
	if(M==(node){1, INF, 0})return ans[str]=(node){0, 0, mp[str]};
	else return ans[str]=(node){M.win^1, M.ops, M.mys+mp[str]};
}

int main()
{

	while(~scanf("%d", &n)){
		mp.clear();
		mst.clear();
		ans.clear();
		for(int i=1;i<=n;i++)scanf("%s", s[i]+1);
		for(int i=1;i<=n;i++){
			int len=strlen(s[i]+1);
			for(int j=1;j<=len;j++){
				string str="";
				int sum=0, ma=0;
				for(int k=j;k<=len;k++){
					str+=s[i][k];
					mst[str].insert(i);
					sum+=s[i][k]-'a'+1;
					ma=max(s[i][k]-'a'+1, ma);
					mp[str]=sum*ma;
				}
			}
		}
		for(auto it=mp.begin();it!=mp.end();it++){
			string str=it->first;
			it->second+=mst[str].size();
		}
		string str="";
		node ansn=dfs(str);
		if(ansn.win){
			printf("Alice\n");
		}
		else printf("Bob\n");
		printf("%d %d\n", ansn.mys, ansn.ops);
	}
}

