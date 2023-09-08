#include<bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#ifdef __linux__
#include "/media/gakshat468/New Volume/CP/algo/debug.h"
#elif _WIN32
#include "D:/CP/algo/debug.h"
#endif
#else
#define debug(...) 468
#endif
#define MOD 1000000007
#define nl <<'\n'
#define sp <<" "<<
#define spe <<" "
#define display_vec(a) for(auto i:a)cout<<i<<" "; cout <<"\n";
#define fast_io ios_base::sync_with_stdio(false); cin.tie(NULL)
#define int long long
bool solve() {
    int n, c;
    cin >> n >> c;
    int ans = 0;
    vector<int> cpow(2 * n + 2, 1), intInverse(n + 5, 1);
    for (int i = 1;i < cpow.size();i++) {
        cpow[i] = cpow[i - 1] * c % MOD;
    }
    for (int i = 2;i < intInverse.size();i++) {
        intInverse[i] = intInverse[MOD % i] * (MOD - MOD / i) % MOD;
    }
    for (int r = 0, v = 1;r <= n;r++) {
        v = v * intInverse[r] % MOD;
        ans += v * cpow[2 * (n - r)] % MOD;
        ans %= MOD;
        v = v * ((intInverse[2] - r + MOD) % MOD) % MOD;
        v = v * (MOD - 4) % MOD * (c - 1) % MOD;
    }

    ans = ans * c % MOD * intInverse[2] % MOD;
    ans += cpow[2 * n] * intInverse[2] % MOD * (2 - c + MOD) % MOD;
    ans %= MOD;
    cout << ans nl;
    return true;
}

int32_t main() {
    fast_io;
#ifdef __linux__
    string path = "/home/gakshat468/CP/";
#elif _WIN32
    string path = "D:/CP/";
#endif
#ifndef ONLINE_JUDGE
    freopen((path + "input.txt").c_str(), "r", stdin);
    freopen((path + "output.txt").c_str(), "w", stdout);
    freopen((path + "error.txt").c_str(), "w", stderr);
#endif
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
        // cout << (solve() ? "YES\n" : "NO\n");
        // cout << (solve() ? "" : "-1\n");
    }
}
