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
#define MOD 998244353
#define nl <<'\n'
#define sp <<" "<<
#define spe <<" "
#define display_vec(a) for(auto i:a)cout<<i<<" "; cout <<"\n";
#define fast_io ios_base::sync_with_stdio(false); cin.tie(NULL)
#define int long long
bool solve()
{
    int n, p;
    cin >> n >> p;
    vector<int> a(n + 1);
    for (int i = 1;i <= n;i++) {
        cin >> a[i];
    }

    vector<int> adj[n + 1];
    for (int i = 0;i < n - 1;i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int H = 7000, T = 1450;
    vector<vector<int>> dp(n + 1, vector<int>(H + 1));
    vector<vector<int>> gp(n + 1, vector<int>(T + 1));
    int countSubgraphs_ans = 0;

    function<void(int, int)> dfs = [&](int u, int parent) {
        for (int i = 1;i <= H;i++) {
            dp[u][i] = (a[u] <= i);
        }

        for (int i = 1;i <= T;i++) {
            gp[u][i] = (a[u] <= (p / i));
        }

        for (auto& v : adj[u]) {
            if (v == parent)continue;
            dfs(v, u);
            for (int i = 1;i <= T;i++) {
                int z = p / i;
                int sum = 0;
                int j;
                for (j = 1;j * j <= z;j++) {
                    if (i * j <= T)
                        sum += (dp[u][j] - dp[u][j - 1] + MOD) * (gp[v][i * j]) % MOD + (dp[v][j] - dp[v][j - 1] + MOD) * gp[u][i * j] % MOD;
                    else
                        sum += (dp[u][j] - dp[u][j - 1] + MOD) * dp[v][p / (i * j)] % MOD;
                    sum %= MOD;
                }
                sum += MOD - dp[u][j - 1] * dp[v][j - 1] % MOD;
                sum %= MOD;
                gp[u][i] = sum;
            }
            vector<int> temp(H + 1);
            for (int i = H;i >= 1;i--) {
                for (int j = H / i;j >= 1;j--) {
                    temp[i * j] += (dp[u][i] - dp[u][i - 1] + MOD) * (dp[v][j] - dp[v][j - 1] + MOD) % MOD;
                    temp[i * j] %= MOD;
                }
            }

            for (int i = 1;i <= H;i++)
                dp[u][i] = (dp[u][i - 1] + temp[i]) % MOD;
        }

        for (int i = 1;i <= H;i++)
            dp[u][i] = (dp[u][i] + 1) % MOD;
        for (int i = 1;i <= T;i++) {
            gp[u][i] = (gp[u][i] + (p / i >= 1)) % MOD;
        }
        countSubgraphs_ans = countSubgraphs_ans + gp[u][1] - 1 + MOD;
        countSubgraphs_ans %= MOD;
        debug(u, dp[u], gp[u]);
        };
    dfs(1, 0);

    cout << countSubgraphs_ans nl;

    return true;
}

int32_t main()
{
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
