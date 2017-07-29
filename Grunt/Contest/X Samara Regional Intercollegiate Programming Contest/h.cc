#include <bits/stdc++.h>
using namespace std;
int n, m;
struct node {
	int num, c, r;
}rec[1050000];
bool cmp(node a, node b){
	return a.num>b.num;
}
int main(){
	scanf("%d%d", &n, &m);
	int tot=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			++tot;
			scanf("%d", &rec[tot].num);
			rec[tot].c=i, rec[tot].r=j;
		}
	}
	sort(rec+1, rec+1+n*m, cmp);
	int c=0, r=0;
	if(rec[1].c==rec[2].c&&rec[2].c==rec[3].c){
		for(int i=4;i<=tot;i++){
			if(rec[i].c!=rec[1].c){
				r=rec[i].r;
				break;
			}
		}
		c=rec[1].c;
	}
	else if(rec[1].r==rec[2].r&&rec[2].r==rec[3].r){
		for(int i=4;i<=tot;i++){
			if(rec[i].r!=rec[1].r){
				c=rec[i].c;
				break;
			}
		}
		r=rec[1].r;
	}
	else if(rec[1].c==rec[2].c){
		c=rec[1].c;
		r=rec[3].r;
	}
	else if(rec[1].r==rec[2].r){
		r=rec[1].r;
		c=rec[3].c;
	}
	else if(rec[3].r==rec[1].r){
		r=rec[1].r;
		c=rec[2].c;
	}
	else if(rec[3].r==rec[2].r){
		r=rec[2].r;
		c=rec[1].c;
	}
	else if(rec[3].c==rec[1].c){
		c=rec[1].c;
		r=rec[2].r;
	}
	else if(rec[3].c==rec[2].c){
		c=rec[2].c;
		r=rec[1].r;
	}
	else {
		c=rec[1].c;
		r=rec[2].r;
	}
	cout<<c<<' '<<r<<endl;
}

