//2016长春J
//就是个垃圾模拟
//特判下前半部分是1000..00的情况(用9999...99)
//其余均前半部分-1再反转(这里甚至不用分奇偶)
//手打了一个垃圾大数，调了一会，还好1A了
#include <bits/stdc++.h>
using namespace std;

struct num{
	int a[1050];
	int len;
	void init(){
		memset(a, 0, sizeof(a));
		len=0;
	}
	void build(char s[]){
		len=strlen(s);
		for(int i=0;i<len;i++)a[i]=s[i]-'0';
	}
	void print(){
		for(int i=0;i<len;i++)printf("%d", a[i]);
		printf("\n");
	}
};

num Minus(num a, num b){
	num ans;
	ans.init();
	int A[1050];
	for(int i=0;i<a.len;i++)A[i]=a.a[i];
	for(int i=0;i<b.len;i++){
		A[a.len-1-i]-=b.a[b.len-1-i];
	}
	for(int i=a.len-1;i>=0;i--){
		while(A[i]<0){
			A[i]+=10;
			A[i-1]--;
		}
	}
	bool ok=false;
	for(int i=0;i<a.len;i++){
		if(A[i])ok=true;
		if(ok)ans.a[ans.len++]=A[i];
	}
	return ans;
}

num maxpal(num a){
	if(a.len==1)return a;
	num ans;
	ans.init();
	bool ok=true;
	for(int i=0;i<a.len/2;i++){
		if(!i&&a.a[i]!=1)ok=false;
		if(i&&a.a[i])ok=false;
	}
	if(ok){
		ans.len=a.len-1;
		for(int i=0;i<ans.len;i++)ans.a[i]=9;
		return ans;
	}
	else {
		ans.len=a.len;
		for(int i=0;i<ans.len/2;i++){
			ans.a[i]=a.a[i];
		}
		ans.a[ans.len/2-1]--;
		for(int i=ans.len/2-1;i>=0;i--){
			if(ans.a[i]<0){
				ans.a[i]+=10;
				ans.a[i-1]--;
			}
		}
		for(int i=ans.len/2;i<ans.len;i++){
			ans.a[i]=ans.a[ans.len-1-i];
		}
		return ans;
	}
}

int tot;
num now;
num ans[50];
char str[1050];

void solve(){
	while(now.len){
		ans[++tot]=maxpal(now);
		now=Minus(now, ans[tot]);
	}
}

int main(){
	int T;
	scanf("%d", &T);
	for(int t=1;t<=T;t++){
		scanf("%s", str);
		tot=0;
		now.init();
		now.build(str);
		solve();
		printf("Case #%d:\n", t);
		printf("%d\n", tot);
		for(int i=1;i<=tot;i++)ans[i].print();
	}
}

