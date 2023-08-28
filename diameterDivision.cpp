#include<bits/stdc++.h>
#define dbg(x) cout<<#x<<" "<<x<<"\n";
#define ll long long int 
#define all(v)  v.begin(),v.end()
using namespace std;
constexpr ll mod=1e9+7;

// help taken from Akshat's code

const int N = 3e5+1;
vector<int> adj[N];

/**
 * @brief takes maximum number of subtrees into account which when chosen and connected to subtree root cur, 
 * diameter of selection shouldn't excee d. which is sum of largest two depth of subtree + 1 (after clipping off some of its decendents)
 * depth starts from 1
 * 
 * @param cur 
 * @param par 
 * @param components 
 * @param d 
 * @return int 
 */

int split_dfs(int cur, int par, int &components, int d){
    int depth = 1;
    vector<int> depths_children({0}); // unexisting children on leftmost side

    for(auto child : adj[cur]){
        if(child != par){
            depths_children.push_back(split_dfs(child, cur, components, d));
        }
    }

    sort(all(depths_children));
    bool ok = false;

    for(int i = 1; i < depths_children.size(); i++){
        if(depths_children[i] + depths_children[i-1] + 1 > d){
            components+=(int)depths_children.size()-i;
            // we split the ith child to make its own components
            // all child from 1, i-1 will be attched to the root
            //this makes depth of root equal to 1 + maximum depth of any child
            depth = depths_children[i-1]+1;
            ok = true;
            break;
        }
    }
    if(!ok)depth = depths_children.back() + 1;

    return depth;
}

void solve(){
    int n;
    cin>>n;
    for(int i = 0; i <= n; i++)adj[i].clear();

    for(int i = 1; i < n; i++){
        int u, v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> Kd(n+1);  // minimum number of components when maximum of diameter of all compoents is d;
    vector<int> Dk(n+1); // minimum of maximum diameter of all components, when number of components is k;

    int root_nLogn = sqrt(n * log2(n)) + 1;

    int last = n;

    for(int d = 1; d <= min(root_nLogn, n); d++){
        int components_with_diameter_d=1;
        split_dfs(1, 0, components_with_diameter_d, d);
        Kd[d] = components_with_diameter_d;
        while(last > 0  && last >= Kd[d]){
            Dk[last--] = d;
        }
    };

    while(last > 0){
        int k = last--;
        int l = 1, r=n;
        int ans = l;
        while(l <= r){
            int mid = l+(r-l)/2; // mid is diameter maybe
            // if Kd(mid) <= k 
            // Dk(k) <= mid
            // otherwise Dk(k) > mid
            
            int components_with_diameter_mid = 1;
            split_dfs(1, 0, components_with_diameter_mid, mid);
            if(components_with_diameter_mid <= k){
                ans = mid;
                r = mid-1;
            }else {
                l = mid+1;
            }
        }
        Dk[k] = ans;
    }

    for(int i = 1; i <= n; i++){
        cout<<Dk[i]-1<<" ";
    }
    cout<<"\n";
}

int main(){
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        int t = 1;
        cin>>t;
        for(int i = 1; i <= t; i++){
            // cout<<"Case #"<<i<<": ";
            solve();
        }
        return 0;
}