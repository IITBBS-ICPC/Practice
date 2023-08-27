#include <bits/stdc++.h>
using namespace std;

#define fast_io                  \
    ios::sync_with_stdio(false); \
    cin.tie(0);
#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define vpi vector<pi>
#define vvpi vector<vpi>
#define pi pair<ll, ll>
#define pb push_back
#define all(x) x.begin(), x.end()


vvi adj;


// DFS function which finds number of components in each subtree for given maximum Diameter
pi dfs(ll cur,ll p,ll maxDiameter) {
    ll subtreeComponents = 0;
    priority_queue<ll> q;
    q.push(0);

    for (auto child : adj[cur])
    {
        if (child != p) 
        {
            auto [childDiameter, childComponents] = dfs(child, cur, maxDiameter);

            subtreeComponents += childComponents;
            q.push(childDiameter);
        }
    }

    while (q.size() > 1) {
        ll diameter1 = q.top();
        q.pop();
        ll diameter2 = q.top();

        if (diameter1 + diameter2 > maxDiameter)
            subtreeComponents++;
        else
        {
            ll curDiameter = diameter1 + 1;
            return {curDiameter,subtreeComponents};
        }
    }

    return {1, subtreeComponents};
}



void solve()
{
    ll n;
    cin>>n;

    adj.assign(n+1,{});

    for(ll i=0;i<n-1;i++)
    {
        ll u,v;
        cin>>u>>v;

        adj[u].pb(v);
        adj[v].pb(u);
    }

    ll minDiameter[n+1];

    for(ll i=0;i<=n;i++)
        minDiameter[i]=n;

    // Part 1 

    ll end=min((ll)n,(ll)(sqrtl(n*log2(n))+5));
    ll d=n;

    for(ll i=0;i<=end;i++)
    {
        ll numComponents=(dfs(1,0,i).second+1);

        minDiameter[numComponents]=min(minDiameter[numComponents],i);

        d=numComponents;
    }

    for(ll i=1;i<n;i++)
        minDiameter[i]=min(minDiameter[i],minDiameter[i-1]);

    // Part 2

    for(ll i=d-1;i>=1;i--)
    {
        ll left=1,right=n,curans=n;

        while(left <= right) 
        {
            ll mid = left + (right-left)/2;

            if(dfs(1,0,mid).second < i)
            {
                curans=min(mid,curans); 
                right=mid-1;
            }
            else
                left=mid+1;
        }

        minDiameter[i]=curans;
    }



    for(ll i=1;i<=n;i++)
        cout<<minDiameter[i]<<" ";

    cout << "\n";
}



signed main()
{
    fast_io;

    ll t = 1;
    cin >> t;

    while (t--)
    {
        solve();
    }


    return 0;
}