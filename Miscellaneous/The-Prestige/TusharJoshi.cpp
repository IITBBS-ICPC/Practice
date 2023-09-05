#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N = 2e5 + 5;

struct node {
    int left, right, par, n;
    int rev;
    ll fa, fb, va, vb;
    node()
        : left(0), right(0), rev(0), fa(0), fb(0), par(0), n(0), va(0), vb(0) {}
};

node nodes[N];

void g(int u) {
    nodes[u].fa =
        nodes[nodes[u].left].fa + nodes[nodes[u].right].fa + nodes[u].va;
    nodes[u].fb =
        nodes[nodes[u].left].fb + nodes[nodes[u].right].fb + nodes[u].vb;
    nodes[u].n = nodes[nodes[u].left].n + nodes[nodes[u].right].n + 1;
}

void splay(int u) {
    int p = nodes[u].par;
    int pp = nodes[p].par;

    if (nodes[p].right == u) {
        nodes[p].right = nodes[u].left;
        nodes[nodes[u].left].par = p;
        nodes[u].left = p;
    } else {
        nodes[p].left = nodes[u].right;
        nodes[nodes[u].right].par = p;
        nodes[u].right = p;
    }

    if (nodes[pp].right == p) {
        nodes[pp].right = u;
    } else {
        nodes[pp].left = u;
    }
    nodes[u].par = pp;
    nodes[p].par = u;

    g(p);
    g(u);
}

void flip(int u) {
    swap(nodes[u].left, nodes[u].right);
    swap(nodes[u].va, nodes[u].vb);
    swap(nodes[u].fa, nodes[u].fb);
    nodes[u].rev ^= 1;
}

void push(int v) {
    if (nodes[v].rev) {
        flip(nodes[v].left);
        flip(nodes[v].right);
        nodes[v].rev = 0;
    }
}

int find(int root, int l) {
    int curr = root;
    while (l) {
        push(curr);
        if (nodes[nodes[curr].left].n >= l) {
            curr = nodes[curr].left;
        } else {
            l -= nodes[nodes[curr].left].n;
            --l;
            if (l) {
                curr = nodes[curr].right;
            }
        }
    }

    if (curr == root) {
        return curr;
    }

    while (true) {
        int p = nodes[curr].par;
        if (p == root) {
            splay(curr);
            break;
        }

        int pp = nodes[p].par;
        if (nodes[pp].left == p && nodes[p].left == curr ||
            nodes[pp].right == p && nodes[p].right == curr) {
            splay(p);
            splay(curr);
        } else {
            splay(curr);
            splay(curr);
        }
        if (pp == root) break;
    }
    return curr;
}

ll rangeSum(int &root, int l, int r) {
    root = find(root, l - 1);
    int more = find(nodes[root].right, r + 1 - (l - 1));
    return nodes[nodes[more].left].fa;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> nodes[i].va;
    }
    for (int i = 1; i <= n; i++) {
        cin >> nodes[i].vb;
    }
    for (int i = 1; i <= n; i++) {
        nodes[i].right = i + 1;
        nodes[i + 1].par = i;
    }
    nodes[n + 2].right = 1;
    nodes[1].par = n + 2;
    nodes[n + 3].right = n + 2;
    nodes[n + 2].par = n + 3;

    int root = n + 2;
    for (int i = n + 1; i; i--) g(i);
    g(n + 2);
    int k = 0;

    while (m--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            l++, r++;
            root = find(root, l - 1);
            int more = find(nodes[root].right, r + 1 - (l - 1));

            flip(nodes[more].left);
            g(more);
            g(root);
        } else if (t == 2) {
            int K;
            cin >> K;
            k = K - k;
        } else {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            a++, b++;

            ll ans = rangeSum(root, a, b);

            // cout << k << ',' <<endl;
            if (k >= d) {
                ans *= -1;
            } else if (k >= c) {
                ll t = rangeSum(root, a, a + k - c);
                // cout << t << ",," << endl;
                ans -= 2 * t;
            }
            cout << ans << endl;
        }
    }
}