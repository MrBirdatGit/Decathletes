    #include<bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    ll p(ll x,ll n){
        ll ans = 1;
        while(n){
            if(n & 1)
                ans *= x;
            n >>= 1;
            x = x * x;
        }
        return ans;
    }
    ll cal(ll x,ll n){
        ll ans = 1;
        for(ll i = 1;i<=n;i++){
            ll tmp =p(x,i);
            if(tmp > 1e12 + 7)
                return 1e12 + 7;
            ans += tmp; 
            if(ans > 1e12 + 7)
                return 1e12 + 7;
        }
        return ans;
    }
    int main(){
        ll n;
        while(~scanf("%lld",&n)){
            // cout<<cal(10,2)<<endl;
            ll R = 1,K = n-1;
            ll maxn = n-1;
            // ll last = 0;
            for(ll rr = 2;rr<=40;rr++){
                ll l = 2,r = (ll)pow(n,1.0/rr);
                // if(r == last) break;
                // last = r;
                while(l <= r){
                    ll mid = (l + r) / 2;
                    ll t = cal(mid,rr);
                    // cout<<rr<<' '<<mid<<' '<<t<<endl;
                    if(t > n + 1){
                        r = mid - 1;
                    }else if(t == n || t == n + 1){
                        ll tmp = rr*mid;
                        if(tmp < maxn){
                            K = mid;
                            R = rr;
                            maxn = tmp;
                        }
                        break;
                    }else{
                        l = mid + 1;
                    }
                }
                // break;
                // cout<<r<<' '<<k<<endl;
            }
            printf("%lld %lld\n",R,K);
        }
    }