#include <bits/stdc++.h>
using namespace std;

#define fast_io                  \
    ios::sync_with_stdio(false); \
    cin.tie(0);
#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define MOD 1000000007LL



ll modinv(ll p, ll q)
{
    ll expo = MOD - 2;
    while (expo)
    {
        if (expo & 1)
            p = (p * q) % MOD;
        q = (q * q) % MOD;
        expo >>= 1;
    }
    return p;
}

const ll N = 20000005;

vector<int> fact(N), facti(N);

void Fact()
{
    fact[0] = 1;
    for (ll i = 1; i < N; i++)
        fact[i] = (i * fact[i - 1]) % MOD;

    facti[N-1] = modinv(1, fact[N-1]);
    for (ll i = N-2; i >= 0; i--)
        facti[i] = ((i+1) * facti[i + 1]) % MOD;
}

ll ncr(ll n, ll r)
{
    if (r > n)
        return 0;

    ll temp = (ll)fact[n] * facti[r] % MOD;
    temp = temp * facti[n - r] % MOD;
    return temp;
}



/*                  CODE      STARTS       HERE        */



int c2Power[10000005];

void solve()
{
    ll n,c;
    cin>>n>>c;

    c2Power[0]=1;

    ll c2=(c*c)%MOD;

    for(ll i=1;i<=n;i++)
    {
        c2Power[i]=(c2*c2Power[i-1])%MOD;
    }

    ll num=0;
    ll cMinusOnePower=1;

    for(ll i=0;i<n;i++)
    {
        ll prod = cMinusOnePower * c2Power[n-i-1] %MOD;
        
        ll cat = modinv((ll)ncr(2*i,i),i+1);

        prod = prod * cat % MOD;
        num = (num + prod) % MOD;

        cMinusOnePower = cMinusOnePower * (c-1) %MOD;
    }

    num = num * c % MOD;
    num = num * (c-1) % MOD;

    ll ans = ((ll)c2Power[n] - num + MOD) % MOD;

    cout<<ans;

    cout << "\n";
}

signed main()
{
    fast_io;

    ll t = 1;
    cin >> t;

    Fact();

    while (t--)
    {
        solve();
    }


    return 0;
}