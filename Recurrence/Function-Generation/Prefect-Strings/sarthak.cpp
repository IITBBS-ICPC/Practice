#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
int powmod(int a,int p=mod-2){
	int res = 1;
	while(p){
		if(p&1)res=(res*1ll*a)%mod;
		p>>=1;
		a=(a*1ll*a)%mod;
	}
	return res;
}
void solve(){
	int n,c;
	cin>>n>>c;
	int c2n = powmod(c,n<<1);
	int ans = c2n;
	int ic2 = powmod((c*1ll*c)%mod);
	int k = (c*1ll*c2n)%mod;
	for(int j=1;j<=n;++j){
		if(j>1){
			k = (k*1ll*((j<<1)-3))%mod;
			k = (k*2ll*powmod(j))%mod;
		}
		k = (k*1ll*(c-1))%mod;
		k = (k*1ll*ic2)%mod;
		ans -= k;
		if(ans<0)ans+=mod;
	}
	cout<<ans<<"\n";
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin>>t;
	while(t--)solve();
}