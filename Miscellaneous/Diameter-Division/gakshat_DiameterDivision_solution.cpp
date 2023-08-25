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
#define ll long long
bool solve()
{
    int n;
    cin >> n;
    vector<int> adj[n + 1];
    for (int i = 0;i < n - 1;i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int flim = sqrt(n * log2(n)) + 2;
    vector<int> g(n + 1, n), f(n + 1);
    vector<int> depth(n + 1);
    function<void(int, int, const int&, int&)> minComponents = [&](int x, int p, const int& d, int& components) {
        depth[x] = 1;
        vector<int> childsDepth = { 0 };
        for (auto& v : adj[x]) {
            if (v == p)continue;
            minComponents(v, x, d, components);
            childsDepth.push_back(depth[v]);
        }
        sort(childsDepth.begin(), childsDepth.end());
        for (int i = 1;i < childsDepth.size();i++) {
            if (childsDepth[i] + childsDepth[i - 1] + 1 > d)components++;
            else depth[x] = childsDepth[i] + 1;
        }
        };

    int last = n;
    for (int d = 1;d <= min(flim, n);d++) {
        f[d] = 1;
        minComponents(1, 0, d, f[d]);
        while (last >= f[d]) {
            g[last] = d;
            last--;
        }
    }

    for (int k = last;k >= 1;k--) {
        int l = 0, r = n;
        while (l + 1 != r) {
            int mid = (l + r) / 2;
            int components = 1;
            minComponents(1, 0, mid, components);
            if (components <= k) r = mid;
            else l = mid;
        }
        g[k] = r;
    }


    for (int i = 1;i <= n;i++) {
        cout << g[i] - 1  spe;
    }
    cout nl;
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
