#include <bits/stdc++.h>
using namespace std;
int n,x,y;
int XOR=0;
int rec[1050];
int tot=0;
int s1[1050];
int tot1=0;
int s2[1050];
int tot2=0;
bool vis[1050];

int solve(int l,int r){
	if(l==r)return s1[l];
	int mid=(l+r)/2;
	int len=mid-l+1;
	printf("? %d ",len);
	for(int i=l;i<=mid;i++){
		printf("%d%c",s1[i],i==mid?'\n':' ');
	}
	fflush(stdout);
	int tmp;
	scanf("%d",&tmp);
	//cout<<"len="<<len<<endl;
	if(len%2==0){
		if(tmp==0)return solve(mid+1,r);
		else return solve(l,mid);
	}
	else {
		if(tmp==x)return solve(mid+1,r);
		else return solve(l,mid);
	}
}

int main(){
	scanf("%d%d%d",&n,&x,&y);
	for(int i=0;(1<<i)<=n&&i<10;i++){
		tot=0;
		for(int j=1;j<=n;j++){
			if(!((j>>i)&1)){
				rec[++tot]=j;
			}
		}
		if(tot==0)continue;
		printf("? %d ",tot);
		for(int j=1;j<=tot;j++)printf("%d%c",rec[j],j==tot?'\n':' ');
		fflush(stdout);
		int tmp;
		scanf("%d",&tmp);
		if(tot%2==0){
			if(tmp)XOR|=(1<<i);
		} 
		else {
			if(tmp==y)XOR|=(1<<i);
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			s2[++tot2]=i;
			vis[i]=true;
			if((i^XOR)<=n&&(i^XOR)>0){
				s1[++tot1]=i^XOR;
				vis[i^XOR]=true;
			}
		}
	}
	//for(int i=1;i<=tot1;i++)printf("%d%c",s1[i],i==tot1?'\n':' '); 
	//for(int i=1;i<=tot2;i++)printf("%d%c",s2[i],i==tot2?'\n':' ');
	//cout<<"XOR="<<XOR<<endl;
	int p1=solve(1,tot1);
	int p2=p1^XOR;
	if(p1>p2)swap(p1,p2);
	printf("! %d %d\n",p1,p2);
	fflush(stdout);
}
