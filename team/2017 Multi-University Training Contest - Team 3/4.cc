#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct trie{
	int ch[500050*31][2];
	int end[500050*31];
	int sz;
	int newnode(){
		ch[sz][0]=ch[sz][1]=-1;
		end[sz]=0;
		return sz++;
	}
	void init(){
		sz=0;
		newnode();
	}
};

trie T[2];

ll val[31][2];

void insert(int num,int id){
	if(id==0){
		int u=0,v=0;
		bool ok=true;
		for(int i=30;i>=0;i--){
			int c=(num>>i)&1;
			if(ok){
				if(c==0&&T[1].ch[v][1]!=-1){
					val[i][0]+=T[1].end[T[1].ch[v][1]];
				}
				else if(c==1&&T[1].ch[v][0]!=-1){
					val[i][1]+=T[1].end[T[1].ch[v][0]];
				}
			}
			if(T[1].ch[v][c]==-1)ok=false;
			else if(ok)v=T[1].ch[v][c];
			if(T[0].ch[u][c]==-1)T[0].ch[u][c]=T[0].newnode();
			T[0].end[T[0].ch[u][c]]++;
			u=T[0].ch[u][c];
		}
	}
	else {
		int u=0;
		bool ok=true;
		for(int i=30;i>=0;i--){
			int c=(num>>i)&1;
			if(T[1].ch[u][c]==-1)T[1].ch[u][c]=T[1].newnode();
			u=T[1].ch[u][c];
			T[1].end[u]++;
		}
	}
}

void del(int num){
	int u=0,v=0;
        bool ok=true;
        for(int i=30;i>=0;i--){
            int c=(num>>i)&1;
            if(ok){
                if(c==0&&T[0].ch[u][1]!=-1){
                    val[i][1]-=T[0].end[T[0].ch[u][1]];
                }
                else if(c==1&&T[0].ch[u][0]!=-1){
                    val[i][0]-=T[0].end[T[0].ch[u][0]];
                }
            }
            if(T[0].ch[u][c]==-1)ok=false;
            else if(ok)u=T[0].ch[u][c];
            //if(T[1].ch[v][c]==-1)T[1].ch[v][c]=T[1].newnode();
            T[1].end[T[1].ch[v][c]]--;
            v=T[1].ch[v][c];
        }
		
}

ll query(int num){
	ll ans=0;
	for(int i=30;i>=0;i--){
		int c=(num>>i)&1;
		ans+=val[i][c];
	}
	return ans;
}

int n;
int a[500050];
ll ans;

int main(){
	int TT;
	scanf("%d",&TT);
	while(TT--){
		T[0].init();
		T[1].init();
		scanf("%d",&n);
		
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
	
		memset(val,0,sizeof(val));
		for(int i=2;i<=n;i++){
			insert(a[i],1);
		}
		ans=0;
		for(int i=2;i<n;i++){
			insert(a[i-1],0);
			del(a[i]);
			ans+=query(a[i]);
			//cout<<ans<<endl;
		}
		printf("%lld\n",ans);
	}
}
