#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef map<int, int> mi;
typedef map<long long, long long> mll;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;

#define pb push_back
#define all(a) a.begin(), a.end()
#define allrev(a) a.rbegin(), a.rend()

#define sp << ' ' <<
#define spl << ' '
#define nl << '\n'

#ifndef ONLINE_JUDGE
#include "/Users/tusharjoshi/cp/files/debug.cpp"
#define debug(x)       \
    cerr << #x << " "; \
    _print(x);         \
    cerr << endl;
#else
#define debug(x)
#endif

int n;
vector<vi> g;

pii dfs(int v, int p, int t_d) {
    int ans = 0;
    vi c_dist = {0, 0};
    for (auto c : g[v]) {
        if (c == p) continue;
        auto [dis, count] = dfs(c, v, t_d);

        ans += count;
        c_dist.pb(dis);
    }

    sort(all(c_dist));

    while (c_dist.size() > 2) {
        int d1 = c_dist.back();
        int d2 = c_dist[c_dist.size() - 2];

        if (d1 + d2 > t_d) {
            ans++;
            c_dist.pop_back();
        } else
            break;
    }

    int mx_dist = c_dist.back();
    return {mx_dist + 1, ans};
}

int K(int d) {
    auto [_, ans] = dfs(1, 0, d);
    return ans + 1;
}

int D(int k) {
    int l = 1, r = n, ans = n;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        int m_k = K(mid);

        if (m_k <= k) {
            ans = min(mid, ans);
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

void solve() {
    cin >> n;

    g.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }

    int lg = log(n);
    int H = sqrt(n * lg) + 2;

    vi ans(n + 2, n);
    int last = n;
    for (int i = 0; i <= min(H, n); i++) {
        int k = K(i);

        ans[k] = min(ans[k], i);

        last = k;
    }

    for (int i = last; i < n; i++) {
        ans[i] = min(ans[i], ans[i - 1]);
    }

    while (--last) {
        ans[last] = D(last);
    }
    for (int i = 1; i <= n; i++) cout << ans[i] spl;
    cout nl;
}

int tc;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("/Users/tusharjoshi/cp/files/input.txt", "r", stdin);
    freopen("/Users/tusharjoshi/cp/files/output.txt", "w", stdout);
    freopen("/Users/tusharjoshi/cp/files/error.txt", "w", stderr);
#endif

    for (cin >> tc; tc > 0; tc--) {
        solve();
    }
    return 0;
}
