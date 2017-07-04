#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int maxn = 10000010;
map<ull,pair<int,int> >M;
char s[maxn];
char que[maxn];
ull Gets(char* str){
    ull ans=0;
    for(int i=0;str[i];i++){
        ans*=131;
        ans+=str[i];
    }
    return ans;
}
int p;
void bulid(ull u){
    while(s[p] != '}'){
        if(s[++p] == '}')
            return;
        ull tmp = u;
        while(s[p] != ':')
            tmp = tmp * 131 + s[p++];
        int l = ++p;
        if(s[p] == '{')
            bulid(tmp*131+'.');
        else while(s[p+1]!=',' && s[p+1]!='}') p++;
        M[tmp] = make_pair(l,p);
        p++;
    }
}
int main(){
    int T,t;
    scanf("%d",&T);
    while(T--){
        M.clear();
        scanf("%s",s);
        p = 0;
        bulid(0);
        scanf("%d",&t);
        while(t--){
            scanf("%s",que);
            ull ans = Gets(que);
            if(M.find(ans) != M.end()){
                pair<int,int> p = M[ans];
                for(int i = p.first;i<=p.second;i++){
                    printf("%c",s[i]);
                }
                printf("\n");
            }else
                printf("Error!\n");
        }
    }
}