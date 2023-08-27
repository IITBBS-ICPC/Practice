#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fo(i,n) for(i=0;i<n;i++)
#define rep(i,n) for(i=1;i<=n;i++)
#define ll long long
#define deb(x) cout<<#x<<"="<<x<<endl
#define deb2(x, y) cout<<#x<<"="<<x<<","<<#y<<"="<<y<<endl
#define F first
#define S second
#define all(x) x.begin(),x.end()
#define sortall(x) sort(all(x))
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

const int mod = 1'000'000'007;
//============================

// implementation help from akshat's code.

void mincomp(int node,int p,int &d,int &comp,vector<vi> &g,vi &depth){
    depth[node]=1;
    vi cdepth={0};
    for(auto child:g[node]){
        if(child==p) continue;
        mincomp(child,node,d,comp,g,depth);
        cdepth.push_back(depth[child]);
    }
    sortall(cdepth);
    for(int i=1;i<cdepth.size();i++){
        if(cdepth[i]+cdepth[i-1]+1>d) comp++;
        else depth[node]=cdepth[i]+1;
    }
}

void solve(){
    int i,j,n,m;
    cin>>n;
    vector<vi> g(n+1);
    rep(i,n-1){
        int a,b; cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int buc=sqrt(n*log2(n));
    vi depth(n+1,0),f(n+1),f2(n+1,n);
    int last=n;
    for(int d=1;d<=min(buc,n);d++) {
        f[d]=1;
        mincomp(1,0,d,f[d],g,depth);
        while(last>=f[d]){
            f2[last]=d;
            last--;
        }
    }
    for(int k=last;k>=1;k--){
        int l=0,r=n;
        while(l+1!=r){
            int mid=(l+r)/2;
            int comp=1;
            mincomp(1,0,mid,comp,g,depth);
            if(comp<=k) r=mid;
            else l=mid;
        }
        f2[k]=r;
    }
    for(int i=1;i<=n;i++){
        cout<<f2[i]-1<<" ";
    }
    cout<<"\n";
}

int main(){
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
