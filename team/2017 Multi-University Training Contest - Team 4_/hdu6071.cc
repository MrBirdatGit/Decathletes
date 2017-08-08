#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll d[4];
ll k;
ll f[5][60500];
ll g[60500];
ll w;
struct node {
	ll dis;
	ll to;	
};
bool operator<(const node& a,const node& b){
	return a.dis>b.dis;
};

priority_queue<node>pq;

int main(){
	ll T;
	scanf("%lld",&T);
	while(T--){
		while(!pq.empty())pq.pop();
		memset(f,-1,sizeof(f));
		scanf("%lld%lld%lld%lld%lld",&k,&d[0],&d[1],&d[2],&d[3]);
		w=2*min(d[0],d[1]);
		for(ll i=k;i<k+w;i++)g[i%w]=i;
		pq.push((node){0,2});
		while(!pq.empty()){
			node tmp=pq.top();
			//cout<<tmp.to<<' '<<tmp.dis<<endl;
			//cout<<"sb"<<tmp.to<<endl;
			pq.pop();
			if(f[tmp.to][tmp.dis%w]!=-1)continue;
			f[tmp.to][tmp.dis%w]=tmp.dis;
			if(tmp.to==1){
				//cout<<"sb1\n";
				pq.push((node){tmp.dis+d[0],2});
				pq.push((node){tmp.dis+d[3],4});
			}
			else if(tmp.to==2){
				//cout<<"sb2\n";
				pq.push((node){tmp.dis+d[0],1});
				pq.push((node){tmp.dis+d[1],3});
			}
			else if(tmp.to==3){
				//cout<<"sb3\n";
				pq.push((node){tmp.dis+d[1],2});
				pq.push((node){tmp.dis+d[2],4});
			}
			else {
				//cout<<"sb4\n";
				pq.push((node){tmp.dis+d[2],3});
				pq.push((node){tmp.dis+d[3],1});
			}
		}
		ll M=1LL<<61;
		//cout<<"cnm"<<g[965]<<endl;
		//cout<<"cnm"<<f[2][965]<<endl;
		for(ll i=0;i<w;i++){
			if(f[2][i]==-1)continue;
			if(f[2][i]>=k)M=min(M,f[2][i]);
			else M=min(M,g[i]);
		}
		printf("%lld\n",M);
	}
}
