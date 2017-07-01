#include<cstdio>
#include<cstring>
using namespace std;

int t[600][600],n,a,i,j;

int main()
{
    int t0;
    scanf("%d",&t0);
    while(t0--)
    {
        scanf("%d",&n);
        memset(t,0,sizeof(t));
        if(n%2==1)
        {
            i=1; j=1;
            for(int ni=1; ni<=n*n; ni++)
            {
                t[i][j]=ni;
                if(j==n)
                {
                    if(n%4==1) i++;
                    else i--;
                }
                else if(i==1)
                {
                    if(j%4==2) i++;
                    else j++;
                }
                else if(i==n)
                {
                    if(j%4==0) i--;
                    else j++;
                }
                else if(i%2==0)
                {
                    if(j%4==1) i++;
                    else if(j%4==3) i--;
                    else j--;
                }
                else if(i%2==1) 
                {
                    if(j%4==2) i++;
                    else if(j%4==0) i--;
                    else j++;
                }
            }
        }
        else if(n%4==0)
        {
            i=1; j=2;
            for(int ni=1; ni<=n*n; ni++)
            {
                t[i][j]=ni;
                if(i==2)
                {
                    if(j%4==2) i++;
                    else if(j==n) i--;
                    else j++;
                }
                else if(i==1)
                {
                    if(j==1) i++;
                    else j--;
                }
                else if(i==n)
                {
                    if(j%4==0) i--;
                    else j++;
                }
                else if(i%2==0)
                {
                    if(j%4==2) i++;
                    else if(j%4==0) i--;
                    else j++;
                }
                else if(i%2==1) 
                {
                    if(j%4==1) i++;
                    else if(j%4==3) i--;
                    else j--;
                }
            }
        }
        else if(n%4==2)
        {
            i=1; j=2;
            for(int ni=1; ni<=n*n; ni++)
            {
                t[i][j]=ni;
                if(i==1)
                {
                    if(j==1) i++;
                    else if(j==2) j--;
                    else if(j%4==2) i++;
                    else j++;
                }
                else if(i==n)
                {
                    if(j==1 || j==2) j++;
                    else if(j==3) i--;
                    else j--;
                }
                else if(i==n-1)
                {
                    if(j==1) i++;
                    else if(j==2) j--;
                    else if(j==n) i++;
                    else if(j%4==0) i--;
                    else j++;
                }
                else if(i%2==0)
                {
                    if(j==1) j++;
                    else if(j==2) i++;
                    else if(j%4==3) i--;
                    else if(j%4==1) i++;
                    else j--;
                }
                else if(i%2==1) 
                {
                    if(j==1) i++;
                    else if(j==2) j--;
                    else if(j%4==0) i--;
                    else if(j%4==2) i++;
                    else j++;
                }
            }
        }
        for(int ti=1; ti<=n; ti++)
        {
            for(int tj=1; tj<n; tj++) printf("%d ",t[ti][tj]);
            printf("%d\n",t[ti][n]);
        }   
    }
    return 0;
}