/*
Contrains : q<=1e6
Solution time complexity: O(q)
addnode O(1)
Kth ancestor O(1)
Check if value already occured O(1)
Rollback O(1)

Explaination:

Solution without Rollback
Idea:
To use a tree like structure to implement the required data structure i.e to addnode we add a child to current node with value x and
to perfrom second operation(- k) we need to go to the Kth ancestor.

Note : the nodes are numbers according to which the were inserted to the tree. So whenever last node is refered means node with highest index.

In this whenever we add node we need to check if the value x has already occured in any of it's ancestors. To do this we store the information
about the last node which has value x and was counted(i.e the last node with value x such that it dosen't has any node with value x in it's subtree).
lets say this node as valLastCountedOn[x]
To check the above we need to check if valLastCountedOn[x] is ancestor if current node v. The height will be known for both of them we just need to check the Kth ancestor.

To find the Kth ancestor we will store the Last node whose height was equal to ht for each height ht(htLastVisBy[ht]).
kth ancestor of current node equals htLastVisBy[currentnodeheight-k].


To Perform the Rollbacks we just use Stack in which the previous values of these(htLastVisBy,valLastCountedOn) for each operation are stored.
*/

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
