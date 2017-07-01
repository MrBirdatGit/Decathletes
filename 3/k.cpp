#include <bits/stdc++.h>
using namespace std;
char str[1050];
char a[1050];
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(str,0,sizeof(str));
        memset(a,0,sizeof(a));
        scanf("%s",str);
        if(strlen(str)==1&&str[0]!='*'){
            printf("2\n");
            continue;
        }
        int c1=0,c2=0;
        int ans=0;
        for(int i=0;str[i];i++){
            if(str[i]=='*')c2++;
            else c1++;
        }
        if(c2+1>c1){
            int add=c2+1-c1;
            ans+=add;                        
            for(int i=0;i<add;i++){
                a[i]='1';
            }
            for(int i=0;str[i];i++){
                a[i+add]=str[i];
            }
        }
        else for(int i=0;str[i];i++)a[i]=str[i];
        //for(int i=0;a[i];i++)printf("%c",a[i]);
        //printf("\n");
        int num=0;
        for(int i=0;a[i];i++){
            if(a[i]=='*'){
                if(num<2){
                    ans++;
                    int m=0;
                    for(int j=i+1;a[j];j++)if(a[j]!='*')m=j;
                    swap(a[i],a[m]);
                    num++;
                }
                else num--;
            }
            else num++;
        }
        int len=strlen(a);
        if(a[len-1]!='*')ans++;
        printf("%d\n",ans);
    }
}

