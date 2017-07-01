#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int inf = 0x3f3f3f3f;
typedef long long ll;
ll book[2000];
bool done[2000];
int main(){
    int T,n,m;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        int t,h,mi;
        char str[3];
        int ans1 = 0;
        ll ans2 = 0;
        memset(book,0,sizeof(book));
        memset(done,0,sizeof(done));
        for(int i = 0;i<m;i++){
            scanf("%d %d:%d %s",&t,&h,&mi,str);
            mi += h * 60;
            if(str[0] == 'A'){
                if(done[t])
                    continue;
                else{
                    done[t] = 1;
                    ans1++;
                    ans2 += mi + book[t];
                }
            }else{
                if(!done[t])
                    book[t] += 20;
            }
        }
        printf("%d %lld\n",ans1,ans2);
    }

}