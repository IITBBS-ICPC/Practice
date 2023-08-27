#include<bits/stdc++.h>
#define ll long long int 
using namespace std;
constexpr ll mod=1e9+7;



template<typename T, typename U>
T pow2(const T x, const U y){
        T res=1,X=x;
        U Y=y;
        while(Y>0)
        {
              if(Y&1)res*=X;
              Y>>=1;
              X*=X;
              X%=mod;
              res%=mod;
        }
        return res;
}

const int N = 1e7+2;
int inv[N];

bool init = [](){
    inv[0] = 1;
    for(int i = 1; i < N; i++){
        inv[i] = 1LL*pow2(1LL*i, mod-2);
    }
    return true;
}();

void solve(){
    ll n, c;
    cin>>n>>c;
    // ans1 = [x^2n] in (2-c)/(2*(1-xc*c))
    ll ans1 = pow2(c, 2*n)*(2-c)%mod;
    if(ans1 < 0)ans1+=mod;
    ll inv2 = inv[2];
    ans1*=inv2;
    ans1%=mod;

    // ans2 = other term
    ll ans2 = pow2(c, 2*n);
    ll term = 1;
    for(int k = 1, p = inv2; k <= n; k++){
        term = term * inv[k] % mod;
        term = term * ((c-1)*(mod-4)%mod)%mod;
        term = term * p % mod;
        ans2 = ans2 + term * pow2(c, 2*n-2*k) % mod;
        ans2 %= mod;
        p--;
        if(p < 0)p+=mod;
    }

    ans2 = ans2 * c % mod;
    ans2 = ans2 * inv2 % mod;

    int ans = ans1+ans2;
    ans%=mod;

    cout<<ans<<"\n";
    
}

int main(){
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        int t = 1;
        cin>>t;
        for(int i = 1; i <= t; i++){
            // cout<<"Case #"<<i<<": ";
            solve();
        }
        return 0;
}