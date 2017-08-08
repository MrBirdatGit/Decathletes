//注意这里fft要开四倍
//求和翻一倍，fft补到2的幂次翻一倍
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
const int MAXN = 400010;
complex x1[MAXN];
int cnt1[MAXN];
ll sum[MAXN];
int T,n;
int main()
{
	scanf("%d",&T);
    while(T--)
    {
    	scanf("%d",&n);
    	int M=0;
    	memset(cnt1,0,sizeof(cnt1));
    	for(int i=1;i<=n;i++){
    		int tmp;
    		scanf("%d",&tmp);
    		M=max(M,tmp);
    		cnt1[tmp]++;
    	}
    	M++;
    	int len=1;
    	while(len<M*2)len<<=1;
        //int len1 = strlen(str1);
        //int len2 = strlen(str2);
        //int len = 1;
        //while(len < len1*2 || len < len2*2)len<<=1;
        for(int i = 0;i < M;i++)
            x1[i] = complex(cnt1[i],0);
        for(int i = M;i < len;i++)
            x1[i] = complex(0,0);
        //求DFT
        fft(x1,len,1);
        for(int i = 0;i < len;i++)
            x1[i] = x1[i]*x1[i];
        fft(x1,len,-1);
        for(int i = 0;i < len;i++)
            sum[i] = (ll)(x1[i].r+0.5);
        for(int i=0;i<len;i++){
        	if(i%2==0)sum[i]-=cnt1[i/2];
        	sum[i]/=2;
        	if(i)sum[i]+=sum[i-1];
        }
        //for(int i=0;i<len;i++){
        //	printf("%d %lld\n",i,sum[i]);
        //}
        ll opp=0;
        for(int i=0;i<len;i++){
        	opp+=cnt1[i]*sum[i];
        }
        ll tot=1LL*n*(n-1)*(n-2)/6;
        printf("%.7f\n",1.0*(tot-opp)/tot);
        
    }
    return 0;
}
