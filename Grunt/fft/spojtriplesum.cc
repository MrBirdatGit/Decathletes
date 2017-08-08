#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;

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
const int MAXN = 300010;
complex x1[MAXN],x2[MAXN];
int a[MAXN],a2[MAXN];
int sum1[MAXN],sum2[MAXN];
int n;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int tmp;
		scanf("%d",&tmp);
		tmp+=20000;
		a[tmp]++;
		a2[2*tmp]++;
	}
    int len = 1;
    while(len<40001*3)len<<=1;
    for(int i=0;i<len;i++)x1[i]=complex(a[i],0);
    fft(x1,len,1);
    for(int i=0;i<len;i++)x1[i]=x1[i]*x1[i]*x1[i];
    fft(x1,len,-1);
    for(int i=0;i<len;i++)sum1[i]=(int)(x1[i].r+0.5);
    
    /*for(int i=0;i<len;i++){
    	if(sum1[i]!=0)printf("%d %d\n",i-60000,sum1[i]);
    }*/
    
    for(int i=0;i<len;i++)x1[i]=complex(a[i],0);
    for(int i=0;i<len;i++)x2[i]=complex(a2[i],0);
    fft(x1,len,1);
    fft(x2,len,1);
    for(int i=0;i<len;i++)x1[i]=x1[i]*x2[i];
    fft(x1,len,-1);
    for(int i=0;i<len;i++)sum2[i]=(int)(x1[i].r+0.5);
    
    /*for(int i=0;i<len;i++){
    	if(sum2[i]!=0)printf("%d %d\n",i-60000,sum2[i]);
    }*/
    //cout<<"ans:\n";
    for(int i=0;i<len;i++){
    	int ans=sum1[i]-sum2[i]*3;
    	if(i%3==0)ans+=2*a[i/3];
    	ans/=6;
    	if(ans!=0)printf("%d : %d\n",i-60000,ans);
    }
    return 0;
}
