#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;

typedef long long ll;

const double PI = acos(-1.0);
//复数结构体
struct complex
{
    double r,i;
    complex(double _r = 0.0,double _i = 0.0)
    {
        r = _r; i = _i;
    }
    complex operator +(const complex &b)
    {
        return complex(r+b.r,i+b.i);
    }
    complex operator -(const complex &b)
    {
        return complex(r-b.r,i-b.i);
    }
    complex operator *(const complex &b)
    {
        return complex(r*b.r-i*b.i,r*b.i+i*b.r);
    }
};
/*
 * 进行FFT和IFFT前的反转变换。
 * 位置i和 （i二进制反转后位置）互换
 * len必须去2的幂
 */
void change(complex y[],int len)
{
    int i,j,k;
    for(i = 1, j = len/2;i < len-1; i++)
    {
        if(i < j)swap(y[i],y[j]);
        //交换互为小标反转的元素，i<j保证交换一次
        //i做正常的+1，j左反转类型的+1,始终保持i和j是反转的
        k = len/2;
        while( j >= k)
        {
            j -= k;
            k /= 2;
        }
        if(j < k) j += k;
    }
}
/*
 * 做FFT
 * len必须为2^k形式，
 * on==1时是DFT，on==-1时是IDFT
 */
void fft(complex y[],int len,int on)
{
    change(y,len);
    for(int h = 2; h <= len; h <<= 1)
    {
        complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j = 0;j < len;j+=h)
        {
            complex w(1,0);
            for(int k = j;k < j+h/2;k++)
            {
                complex u = y[k];
                complex t = w*y[k+h/2];
                y[k] = u+t;
                y[k+h/2] = u-t;
                w = w*wn;
            }
        }
    }
    if(on == -1)
        for(int i = 0;i < len;i++)
            y[i].r /= len;
}
const int MAXN = 200010;
complex x1[MAXN],x2[MAXN];
int r[MAXN],c[MAXN];
int n,m,T,q;
int sum[MAXN];
bool vis[MAXN];
int main()
{
	scanf("%d",&T);
    for(int tt=1;tt<=T;tt++)
    {
       	scanf("%d%d%d",&n,&m,&q);
       	memset(r,0,sizeof(r));
       	memset(c,0,sizeof(c));
       	memset(vis,false,sizeof(vis));
       	for(int i=1;i<=n;i++)r[i]=1;
       	for(int i=1;i<=m;i++)c[i]=1;
       	for(int i=1;i<=q;i++){
       		int x,y;
       		scanf("%d%d",&x,&y);
       		x=n-x+1;
       		r[x]=0;
       		c[y]=0;
       		vis[x+y]=true;
       	}
        int len = 1;
        while(len < (n+1)*2 || len < (m+1)*2)len<<=1;
        for(int i = 0;i < n+1 ;i++)
            x1[i] = complex(r[i],0);
        for(int i = n+1;i < len;i++)
            x1[i] = complex(0,0);
        for(int i = 0;i < m+1;i++)
            x2[i] = complex(c[i],0);
        for(int i = m+1;i < len;i++)
            x2[i] = complex(0,0);
        //求DFT
        fft(x1,len,1);
        fft(x2,len,1);
        for(int i = 0;i < len;i++)
            x1[i] = x1[i]*x2[i];
        fft(x1,len,-1);
        ll ans=0;
        for(int i = 0;i < len;i++){
            sum[i] = (int)(x1[i].r+0.5);
            //printf("%d %d\n",i,sum[i]);
        	if(!vis[i])ans+=sum[i];
        }
        printf("Case %d: %lld\n",tt,ans);
    }
    return 0;
}
