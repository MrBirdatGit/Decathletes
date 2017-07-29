//好题
//注意到只有四个字母，循环串的长度不超过10
//考虑建400个树状数组，则就是单点更新区间查询
//而同类的树状数组可以合并，又压缩了10倍空间
#include <bits/stdc++.h>
using namespace std;
int idx(char c){
	if(c=='A')return 0;
	if(c=='G')return 1;
	if(c=='C')return 2;
	return 3;
}

int c[4][11][105000];
char str[105000];

int lowbit(int x){
	return x&(-x);
}

void update(int p, int typ, int add){
	for(int i=1;i<=10;i++){
		int pos=p;
		while(pos<=100020){
			c[typ][i][pos]+=add;
			int rk=(pos+i-1)/i;
			int adrk=lowbit(rk);
			pos+=adrk*i;
		}
	}
}

int query(int p, int typ, int i){
	int pos=p;
	int ans=0;
	while(pos>0){
		ans+=c[typ][i][pos];
		int rk=(pos+i-1)/i;
		int adrk=lowbit(rk);
		pos-=adrk*i;
	}
	return ans;
}

int main()
{
	memset(c, 0, sizeof(c));
	scanf("%s", str+1);
	for(int i=1;str[i];i++){
		update(i, idx(str[i]), 1);
	}
	int q;
	scanf("%d", &q);
	while(q--){
		int tag;
		scanf("%d", &tag);
		if(tag==2){
			int l, r;
			char s[20];
			scanf("%d%d%s", &l, &r, s);
			int len=strlen(s);
			int ans=0;
			for(int i=0;i<len;i++){
				int pl=l+i-len;
				int tim=(r-l+1)/len;
				int pr=l+i+tim*len;
				while(pr+len<=r)pr+=len;
				while(pr>r)pr-=len;
				ans+=query(pr, idx(s[i]), len)-query(pl, idx(s[i]), len);
			}
			printf("%d\n", ans);
		}
		else {
			int x;
			char s[5];
			scanf("%d%s", &x, s);
			update(x, idx(str[x]), -1);
			update(x, idx(s[0]), 1);
			str[x]=s[0];
		}
	}
}

