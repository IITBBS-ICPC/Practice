#include <bits/stdc++.h>

#define ll int

using namespace std;

ll m = 1e9 + 7;


ll sum(ll a, ll b) { return ((a % m) + (b % m)) % m; }

ll sub(ll a, ll b) { return (m + (a % m) - (b % m)) % m; }

ll mul(ll a, ll b) { return ((a % m) * 1ll * (b % m)) % m; }

ll mul(vector<ll> op) {
    ll ans = 1;
    for (auto x : op) ans = mul(ans, x);
    return ans;
}

ll binexp(ll a, ll b) {
    a %= m;
    ll ans = 1;
    for (; b; b >>= 1, a = mul(a, a))
        if (b & 1) ans = mul(ans, a);
    return ans;
}

ll frac(ll a, ll b) { return mul(a, binexp(b, m - 2)); }

vector<ll> fact, facti;

ll cat(ll n) { return mul(vector<ll>({fact[2 * n], facti[n], facti[n + 1]})); }

void solve() {
    ll n, c;
    cin >> n >> c;

    fact.assign(2 * n + 5, 1);
    facti.assign(2 * n + 5, 1);

    // modularInverse(n);
    for (int i = 2; i < 2 * n + 5; i++) {
        fact[i] = mul(fact[i - 1], i);
    }
    facti[n + 2] = frac(1, fact[n + 2]);
    for (int i = n + 1; i; i--) {
        facti[i] = mul(facti[i + 1], i + 1);
    }

    ll ans = binexp(c, 2 * n);

    vector<ll> c2pow(n + 5, 1);
    ll cSub1Pow = 1;
    ll c2 = mul(c, c);
    for (int i = 1; i < n + 5; i++) c2pow[i] = mul(c2pow[i - 1], c2);

    ll rem = 0;
    for (int i = 0; i < n; i++) {
        ll term = mul(vector<ll>{cat(i), cSub1Pow, c2pow[n - 1 - i]});
        cSub1Pow = mul(cSub1Pow, c - 1);
        rem = sum(rem, term);
    }
    rem = mul(vector<ll>({c, c - 1, rem}));
    ans = sub(ans, rem);

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;

    // cout << frac(1, 3) << endl;

    while (t--) {
        solve();
    }
}