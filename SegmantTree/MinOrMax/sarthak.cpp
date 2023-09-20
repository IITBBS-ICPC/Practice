#include <bits/stdc++.h>
using namespace std;
class SegTree{
    struct node{
        int lazyCurLengthAdd;
        int lazyAdd,lazySet;
        bool isLazySet;
        node():
            lazyCurLengthAdd(0),
            isLazySet(false){}
        void lazyUpdateLength(int val){
            if(isLazySet){
                lazySet+=val;
            }
            else{
                lazyCurLengthAdd+=val;
            }
        }
        void lazyApplySet(int add,int val){
            if(isLazySet){
                lazyAdd+=(add+((lazySet+1)>>1));
                lazySet=val;
            }
            else{
                isLazySet = true;
                lazyAdd = add;
                lazySet = val;
            }
        }
        int get(){
            int ans = (lazyCurLengthAdd+1)>>1;
            if(isLazySet)
                ans += (lazyAdd+((lazySet+1)>>1));
            return ans;
        }
    };
    int rangeL,rangeR;
    vector<node> nodes;
    void push(int u,int lc,int rc){
        if(nodes[u].lazyCurLengthAdd){
            nodes[lc].lazyUpdateLength(nodes[u].lazyCurLengthAdd);
            nodes[rc].lazyUpdateLength(nodes[u].lazyCurLengthAdd);
            nodes[u].lazyCurLengthAdd = 0;
        }
        if(nodes[u].isLazySet){
            nodes[lc].lazyApplySet(nodes[u].lazyAdd,nodes[u].lazySet);
            nodes[rc].lazyApplySet(nodes[u].lazyAdd,nodes[u].lazySet);
            nodes[u].isLazySet = false;
        }
    }
    void update(int i,int l,int r,int L,int R){
        if((l==L)&&(r==R)){
            nodes[i].lazyUpdateLength(1);
        }
        else{
            int mid = l+((r-l)>>1);
            int z = (mid+1-l)<<1;
            push(i,i+1,i+z);
            if(R<=mid){
                update(i+1,l,mid,L,R);
                nodes[i+z].lazyApplySet(0,0);
            }
            else if(L>mid){
                update(i+z,mid+1,r,L,R);
                nodes[i+1].lazyApplySet(0,0);
            }
            else{
                update(i+1,l,mid,L,mid);
                update(i+z,mid+1,r,mid+1,R);
            }
        }
    }
    int get(int i,int l, int r,int x){
        if(l==r)
            return nodes[i].get();
        int mid = l+((r-l)>>1);
        int z = (mid+1-l)<<1;
        push(i,i+1,i+z);
        if(x<=mid)
            return get(i+1,l,mid,x);
        return get(i+z,mid+1,r,x);
    }
    public:
        SegTree(int _rangeL,int _rangeR):
            rangeL(_rangeL),
            rangeR(_rangeR){
                nodes.resize((_rangeR-_rangeL+1)<<1);
        }
        void fullUpdate(){
            nodes[0].lazyApplySet(0,0);
        }
        void update(int L,int R){
            update(0,rangeL,rangeR,L,R);
        }
        int get(int x){
            return get(0,rangeL,rangeR,x);
        }
    
};
vector<int> solve(vector<int> a,int m){
    SegTree S(1,m);
    int n = a.size()-1;
    vector<int> occ(m+1);
    for(int i=1;i<=n;++i){
        ++occ[a[i]];
        int l = min(a[i],a[i-1])+1;
        int r = max(a[i],a[i-1])-1;
        if(l<=r)
            S.update(l,r);
        else
            S.fullUpdate();
    }
    vector<int> ans(m+1,-1);
    for(int i=1;i<=m;++i){
        if(occ[i])
            ans[i] = n-occ[i]+S.get(i);
    }
    return ans;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m;
    cin>>n>>m;
    vector<int> a(n);
    for(auto &x:a)
        cin>>x;
    a.push_back(a[0]);
    vector<int> ans1 = solve(a,m);
    a.push_back(a[1]);
    vector<int> b(a.begin()+1,a.end());
    vector<int> ans2 = solve(b,m);
    for(int i=1;i<=m;++i)
        cout<<min(ans1[i],ans2[i])<<" ";
    cout<<"\n";
}