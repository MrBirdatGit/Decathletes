#include <bits/stdc++.h>
using namespace std;
int a, b;
double c;
int main()
{
	while(~scanf("%d%d%lf", &a, &b, &c)){
		if(a==0&&b==0&&c==0)break;
		if(a==1){
			printf("0\n");
		}
		else printf("%d\n", a-1);
	}
}

