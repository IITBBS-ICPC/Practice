#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fo(i,n) for(i=0;i<n;i++)
#define rep(i,n) for(i=1;i<=n;i++)
#define int long long
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

int binpow(int a,int n){
    int res=1ll;
    while(n>0ll){
        if(n&1ll) res=(res*a)%mod;
        a=(a*a)%mod;
        n=n>>1ll;
    }
    return res;
}

const int N=10000001;
vi invfact(N),c2(N),_44c(N);
int inv2=binpow(2ll,mod-2ll);

void solve(){
    int i,j,n,c;
    cin>>n>>c;
    int cs=(c*c)%mod;
    c2[0]=1ll;
    rep(i,n) c2[i]=(c2[i-1]*cs)%mod;
    cs=((4ll*c)%mod-4ll+mod)%mod;
    _44c[0]=1;
    rep(i,n) _44c[i]=(_44c[i-1]*cs)%mod;
    int l=(c*inv2)%mod;
    l=(l*c2[n])%mod;
    l=(c2[n]-l+mod)%mod;
    int r=(c*inv2)%mod;
    int temp=0ll,curr=1;
    for(i=n;i>=0;i--){
        int idx=n-i;
        int x=(c2[i]*_44c[idx])%mod;
        x=(x*invfact[idx])%mod;
        x=(x*curr)%mod;
        if(idx%2) x=-x;
        temp=(temp+x+mod)%mod;
        curr=(curr*((inv2-idx+mod)%mod))%mod;
    }
    r=(r*temp)%mod;
    cout<<(l+r)%mod<<"\n";
}

signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    int t=1,i,j;
    cin>>t;
    int f=1ll;
    rep(i,N) f=(f*i)%mod;
    invfact[N]=binpow(f,mod-2ll);
    for(i=N;i>=1;i--) invfact[i-1]=(invfact[i]*i)%mod;
    while(t--){
        solve();
    }
    return 0;
}