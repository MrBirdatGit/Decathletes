/* 数学 */
/* 扩展欧几里得 */
/* 素数线性筛 */
/* 中国剩余定理 */
/* 卢卡斯定理 */
/* 逆元 */
/* 欧拉函数 */
/* 莫比乌斯函数 */
/* 威佐夫博弈 */
/* 反NIM博弈 */
/* NTT/FFT/FWT */
/* Miller_Rabin */
/* 自适应simpson */
/* 线性递推m^2logn */
/* polya定理 */

/* 数据结构 */
/* 单调队列 */
/* 吉司机线段树 */
/* 主席树 */
/* splay */

/* 字符串 */
/* 后缀数组 */
/* AC自动机 */

/* 图论 */
/* lca */
/* tarjan */
/* 2-sat */
/* 网络流 */
/* KM */
/* 欧拉图 */
/* 点分治 */


/* dp */
/* 数位dp */
/* 斜率优化 */
/* 四边形优化 */

/* 其他 */
/* 输入外挂 */
/* bitset */
/* O(1)快速乘 */

//扩展欧几里得
//求ax+by=gcd(a, b)的解
void exgcd(ll a, ll b, ll &x, ll &y){
	if(b==0){
		x=1, y=0;
		return ;
	}
	exgcd(b, a%b, x, y);
	ll tmp=x;
	x=y;
	y=tmp-(a/b)*y;
}

//素数线性筛
const int maxn=205000;

bool vis[maxn];
int prime[maxn];
int tot;
void init(){
	memset(vis, false, sizeof(vis));
	tot=0;
	for(int i=2;i<maxn;i++){
		if(!vis[i])prime[++tot]=i;
		for(int j=1;j<=tot&&prime[j]*i<maxn;j++){
			vis[prime[j]*i]=true;
			if(i%prime[j]==0)break;
		}
	}
}

//中国剩余定理
//正整数m1, m2, ..., mk两两互素, 则同余方程组
//
//x%m1==a1
//x%m2==a2
//
//x%mk==ak
//
//在模M=m1*m1*...*mk下的解唯一
//
//x%M==sigma(ai*Mi*inv(Mi))
//
//Mi=M/mi, inv(Mi)为Mi模mi的逆元
int CRT(int a[], int m[], int n){
	int M=1;
	int ans=0;
	for(int i=1;i<=n;i++)M*=m[i];
	for(int i=1;i<=n;i++){
		int x, y;
		int Mi=M/m[i];
		exgcd(Mi, m[i], x, y);//m[i]不一定是素数, 故要用exgcd求逆元
		ans=(ans+a[i]*Mi*x)%M;
	}
	if(ans<0)ans+=M;
	return ans;
}

//卢卡斯定理
//rm to do

//逆元
//ans=(a/b)%m=(a%(mb))/b
//fermat小定理
//exgcd
//o(n)预处理mod的逆元
int mod;
int inv[maxn];

void init(){
	inv[1] = 1;
	for(int i=2;i<mod;i++){
		inv[i]=inv[mod%i]*(mod-mod/i)%mod;
	}
}

//欧拉函数
//rm to do

//莫比乌斯函数
//rm to do

