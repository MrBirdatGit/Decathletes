#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
char s[1050000];
char t[1050000];
ll cnts[27];
ll cntt[27];
bool check(ll tim){
	ll tmp=0;
	for(int i=0;i<26;i++){
		if(cnts[i]<cntt[i]*tim)tmp+=cntt[i]*tim-cnts[i];
	}
	return tmp<=cnts[26];
}
int main(){
	scanf("%s%s", s, t);
	for(int i=0;s[i];i++){
		if(s[i]=='?')cnts[26]++;
		else cnts[s[i]-'a']++;
	}
	for(int i=0;t[i];i++){
		cntt[t[i]-'a']++;
	}
	ll l=0, r=1e6;
	ll ans=-1;
	while(l<=r){
		if(r-l<=1){
			if(check(r))ans=r;
			else ans=l;
			break;
		}
		ll mid=(l+r)/2;
		if(check(mid))l=mid;
		else r=mid;
	}
	int st=0;
	for(int i=0;s[i];i++){
		if(s[i]!='?')printf("%c", s[i]);
		else {
			while(st<26&&cnts[st]>=cntt[st]*ans){
				st++;
			}
			if(st==26)printf("a");
			else {
				printf("%c", st+'a');
				cnts[st]++;
			}
		}
	}
	printf("\n");
}

