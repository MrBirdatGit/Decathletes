#include <bits/stdc++.h>
using namespace std;

struct node{
	int c,r,id;
}rec[105000];

bool operator<(const node& a,const node& b){
	return a.c<b.c;
}

bool cmp(node a,node b){
	if(a.c==b.c)return a.r<b.r;
	return a.c<b.c;
}

int pre[105000];
int ans[105000];

int C;
int n;
int tot=0;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d %d",&rec[i].c,&rec[i].r);
		rec[i].id=i;
	}
	C=rec[n].c;
	sort(rec+1,rec+1+n,cmp);
	pre[1]=1;
	for(int i=2;i<=n;i++){
		if(rec[i].r>rec[pre[i-1]].r)pre[i]=i;
		else pre[i]=pre[i-1];
	}
	int r=1;
	while(1){
		if(r>=C){
			ans[++tot]=n;
			break;
		}
		node tmp=(node){r,0,0};
		int p=upper_bound(rec+1,rec+1+n,tmp)-rec-1;
		if(p==0||rec[pre[p]].r<=r)return 0*printf("No such luck\n");
		p=pre[p];
		ans[++tot]=rec[p].id;
		r=rec[p].r;
	}
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++)printf("%d%c",ans[i],i==tot?'\n':' ');
}
