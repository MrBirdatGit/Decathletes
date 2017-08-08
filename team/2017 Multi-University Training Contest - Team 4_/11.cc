#include<bits/stdc++.h>
using namespace std;
int lig[10]={1110111,10010,1011101,1011011,111010,1101011,1101111,1010010,1111111,1111011};
char c[10][30];
int pan(int x)
{
	int num=0;
	if(c[0][x+1]=='X') num+=1000000;
	if(c[1][x]=='X') num+=100000;
	if(c[1][x+3]=='X') num+=10000;
	if(c[3][x+1]=='X') num+=1000;
	if(c[4][x]=='X') num+=100;
	if(c[4][x+3]=='X') num+=10;
	if(c[6][x+1]=='X') num+=1;
	//cout<<num<<endl;
	for(int i=0; i<10; i++)
	if(num==lig[i]) return i;
	return 0;
	//cout<<"hehe";
}
bool ok(int x,int i){
	if(c[0][x+1] =='X'&& i == 0) return 1;
	if(c[1][x] =='X' && i ==1) return 1;
	if(c[1][x+3] =='X' && i == 2) return 1;
	if(c[3][x+1] =='X' && i == 3) return 1;
	if(c[4][x] == 'X' && i == 4) return 1;
	if(c[4][x+3] == 'X' && i == 5) return 1;
	if(c[6][x+1] == 'X' && i == 6) return 1;
	return 0;
}
int cal(int x){
	for(int i = 0;i<10;i++){
		int tmp = lig[i];
		bool flag = 0;
		for(int j = 6;j>-1;j--){
			if(ok(x,j) != tmp%10)
				flag = 1;
			tmp/=10;
		}
		if(!flag)
			return i;
	}
}
int main()
{
	int t;	
	scanf("%d",&t);
	while(t--)
	{
		
		
		for(int i=0; i<7; i++) 	scanf("%s",c[i]);
		
		//cout<<pan(0)<<endl;
		printf("%d%d:%d%d\n",cal(0),cal(5),cal(12),cal(17));
		
	}
}
