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

int32_t main()
{
    int q = 1;
    cin >> q;
    vector<array<int, 5>> state_stack;
    vector<int> htLastVisBy(q + 1), valLastCountedOn(1e6 + 1), height(q + 1), countnode(q + 1), node(1), ans(q + 1);
    int v = 0;
    function<void(int)> addnode = [&](int x) {
        int u = v;
        v = node.size();
        node.push_back(x);
        height[v] = height[u] + 1;
        ans[v] = ans[u];

        //Check if this value is already there in ancestors
        if (valLastCountedOn[x] == 0
            || height[valLastCountedOn[x]] >= height[v]
            || node[htLastVisBy[height[valLastCountedOn[x]]]] != x
            )
            countnode[v] = 1;

        state_stack.push_back({ u,x,valLastCountedOn[x],height[v],htLastVisBy[height[v]] });
        if (countnode[v]) {
            ans[v]++;
            valLastCountedOn[x] = v;
        }
        htLastVisBy[height[v]] = v;
        return;
        };

    function<void(int)> jumpAncestor = [&](int k) {
        int u = v;
        v = htLastVisBy[height[v] - k];
        state_stack.push_back({ u,-1 });
        };

    function<void()> rollBack = [&]() {
        auto [u, x, Vx, ht, Vht] = state_stack.back();
        state_stack.pop_back();
        if (x < 0) {
            v = u;
            return;
        }
        v = u;
        valLastCountedOn[x] = Vx;
        htLastVisBy[ht] = Vht;
        };
    for (int qi = 0;qi < q;qi++) {
        char querytype;
        cin >> querytype;
        switch (querytype)
        {
        case '+':
            int x;
            cin >> x;
            addnode(x);
            break;
        case '-':
            int k;
            cin >> k;
            jumpAncestor(k);
            break;
        case '!':
            rollBack();
            break;
        case '?':
            cout << ans[v] << endl;
            break;
        }
        // debug(v, height, valLastCountedOn, htLastVisBy);
    }
}
