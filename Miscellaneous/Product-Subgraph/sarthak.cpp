#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
const int mod = 998244353;
void combine(vector<int> &f, vector<int> &F, vector<int> &g, vector<int> &G, int P)
{
    vector<int> h(f.size()), H(h.size());
    for (int i = 1; i < f.size(); ++i)
    {
        for (int j = 1; (i * j) < f.size(); ++j)
        {
            h[i * j] = (h[i * j] + ((f[i] - f[i - 1]+mod) * 1ll * (g[j] - g[j - 1]+mod))) % mod;
        }
    }
    for (int i = 1; i < h.size(); ++i)
    {
        h[i] += h[i - 1];
        if (h[i] >= mod)
            h[i] -= mod;
    }
    for (int i = 1; i < F.size(); ++i)
    {
        int z = sqrt((P / i));
        for (int j = 1; j <= z; ++j)
        {
            if (i * j < F.size())
                H[i] = (H[i] + ((f[j] - f[j - 1]+mod) * 1ll * G[i * j])) % mod;
            else
                H[i] = (H[i] + ((f[j] - f[j - 1]+mod) * 1ll * g[P / (i * j)])) % mod;
        }
        for (int j = 1; j <= z; ++j)
        {
            if (i * j < F.size())
                H[i] = (H[i] + ((g[j] - g[j - 1]+mod) * 1ll * F[i * j])) % mod;
            else
                H[i] = (H[i] + ((g[j] - g[j - 1]+mod) * 1ll * f[P / (i * j)])) % mod;
        }
        H[i] = (H[i] - ((f[z] * 1ll * g[z])%mod)) % mod;
        if (H[i] < 0)
            H[i] += mod;
    }
    for (int i = 0; i < f.size(); ++i)
    {
        f[i] += h[i];
        if (f[i] >= mod)
            f[i] -= mod;
    }
    for (int i = 0; i < F.size(); ++i)
    {
        F[i] += H[i];
        if (F[i] >= mod)
            F[i] -= mod;
    }
}
pair<vector<int>, vector<int>> dfs(int u, int p, vector<vector<int>> &g, vector<int> &a, int H, int T, int P, int &ans)
{
    vector<int> f(H), F(T);
    for (int i = a[u]; i < H; ++i)
        f[i] = 1;
    for (int i = 1; i < T; ++i)
        F[i] = a[u] <= (P / i);
    for (auto v : g[u])
    {
        if (v != p)
        {
            pair<vector<int>, vector<int>> child = dfs(v, u, g, a, H, T, P, ans);
            combine(f, F, child.first, child.second, P);
        }
    }
    ans += F[1];
    if (ans >= mod)
        ans -= mod;
    return make_pair(f, F);
}
void solve()
{
    int n, p;
    cin >> n >> p;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
	int H = sqrt(p)+1;
    auto calT = [&](int h)
    {
        return (p + h) / h;
    };
    while (H * log(H) < (2 * sqrtl(p *1ll* calT(H))))
        ++H;
    int T = max(calT(H), 2);
    int ans = 0;
    dfs(0, 0, g, a, H, T, p, ans);
    cout << ans << "\n";
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
        solve();
}