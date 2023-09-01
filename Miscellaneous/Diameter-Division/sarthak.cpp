#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
pair<bool,int> solveMinKNode(int u,int p,int l,vector<int> *g,int &ans){
	int done = 0;
	int deep = 0;
	for(int v:g[u]){
		if(v!=p){
			pair<bool,int> child = solveMinKNode(v,u,l,g,ans);
			if(child.first){
				done = max(child.second,done);
			}
			else{
				deep = max(child.second,deep);
			}
		}
	}
	++deep;
	if(deep<=done){
		return make_pair(true,done-1);
	}
	else if(deep==l){
		++ans;
		return make_pair(true,l-1);
	}
	else{
		return make_pair(false,deep);
	}
}
pair<bool,int> solveMinKEdge(int u,int p,int l,vector<int> *g,int &ans){
	int deep = 0;
	int done = -1;
	for(int v:g[u]){
		if(v!=p){
			pair<bool,int> child = solveMinKEdge(v,u,l,g,ans);
			if(child.first){
				done = max(done,child.second-1);
			}
			else if(child.second==(l-1)){
				++ans;
				done = (l-1);
			}
			else{
				deep = max(deep,child.second+1);
			}
		}
	}
	if(deep<=done){
		return make_pair(true,done);
	}
	else{
		return make_pair(false,deep);
	}
}
void solve(){
	int n;
	cin>>n;
	vector<int> g[n];
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        --u;--v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
	int Kmin = n;
	vector<int> ans(n+1,n);
	int r = 0;
	while(g[r].size()>1)++r;
    auto fsolve = [&](int h){
        int curK = 0;
		int H = (h>>1)+1;
		if(h&1){
			pair<bool,int> cur = solveMinKEdge(g[r][0],r,H,g,curK);
			if((!cur.first)||(cur.second<1))
				++curK;
		}
		else{
			pair<bool,int> cur = solveMinKNode(r,r,(h>>1)+1,g,curK);
			if(!cur.first)++curK;
		}
        return curK;
		
    };
	for(int h=0;h<(min(Kmin*15,n));++h){
        int curK = fsolve(h);
        Kmin = min(Kmin,curK);
		ans[curK] = min(ans[curK],h);
	}
    for(int i=1;i<=n;++i)
		ans[i] = min(ans[i],ans[i-1]);
    int L = min(Kmin*15,n),R=n;
    for(int i=Kmin;i>=0;--i){
        int l = L, r = R, h = ans[i];
        while(l<=r){
            int mid = (l+r)>>1;
            if(fsolve(mid)<=i){
                ans[i]=min(ans[i],mid);
                r=mid-1;
            }
            else l = mid+1;
        }
        L = ans[i];
    }
	for(int i=1;i<=n;++i){
		cout<<ans[i]<<" ";
	}
	cout<<"\n";
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin>>t;
	while(t--)solve();
}