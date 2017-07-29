//#include <bitset>
//using std::bitset;
//bitset<n>b;
//b.any() any 1?
//b.none() no 1?
//b.count() number of 1?
//b.size() size?
//b.set() set all pos 1
//b.reset() set all pos 0
//b.flip() 1->0, 0->1

//k中浓度为ai/1000的液体配成n/1000的浓度至少需要多少升
//每种溶液均为整数升
//易知若有解必小于1000，dp过程用bitset加速

#include <bits/stdc++.h>
using namespace std;

int n, k;
bool a[1050];
bitset<2050>b[2];

int main(){
	scanf("%d%d", &n, &k);
	for(int i=1;i<=k;i++){
		int x;
		scanf("%d", &x);
		a[x]=true;
	}
	b[0][1000]=1;
	for(int i=0;i<=1000;i++){
		if(i!=0&&b[i%2][1000]){
			printf("%d\n", i);
			return 0;
		}
		int now=i%2;
		b[now^1].reset();
		for(int j=0;j<=1000;j++){
			if(a[j]){
				b[now^1]|=(b[now]<<j)>>n;
			}
		}
	}
	printf("-1\n");
}

