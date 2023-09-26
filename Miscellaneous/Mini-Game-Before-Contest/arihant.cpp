#include<bits/stdc++.h>
using namespace std;

int n,m;

vector<vector<int>> adj;
vector<int> vis,in,out;
string state,player,isJoker;

void create_graph(int n)
{
    adj.assign(n+1,{});
    vis.assign(n+1,0);
    in.assign(n+1,0);
    out.assign(n+1,0);
    state.assign(n+1,'D');
}

void dfs(int cur)
{
    if(vis[cur])
        return;

    vis[cur]=1;

    for(auto x:adj[cur])
    {
        if(vis[x])
            continue;
            
        in[x]--;

        int pos=(x-1)/n;

        // Case 1 (A,A,0 and B,B,0)

        if(state[cur]==player[pos] && isJoker[pos]=='0')
        {
            state[x]=state[cur];
            dfs(x);
        }

        // Case 2 (A,B,1 and B,A,1)

        if(state[cur]!=player[pos] && isJoker[pos]=='1')
        {
            state[x]=state[cur];
            dfs(x);
        }

        // Case 3 (A,A,1 and B,B,1)

        if(in[x]==0 && state[cur]==player[pos] && isJoker[pos]=='1')
        {
            state[x]=state[cur];
            dfs(x);
        }

        // Case 4 (A,B,0 and B,A,0)

        if(in[x]==0 && state[cur]!=player[pos] && isJoker[pos]=='0')
        {
            state[x]=state[cur];
            dfs(x);
        }
    }
}

void solve()
{
    cin>>n>>m;

    create_graph(6*n); // Reverse graph with 6 states for each vertex

    for(int i=0;i<m;i++)
    {
        int u,v;
        cin>>u>>v;

        for(int j=0;j<6;j++)
        {
            int st=(v+((j+1)%6)*n),ed=u+j*n;
            adj[st].push_back(ed);
            out[st]++;
            in[ed]++;
        }
    }

    cin>>player>>isJoker;

    //

    for(int i=1;i<=6*n;i++)
        if(in[i]==0)
        {
            if(player[(i-1)/n]=='A')
                state[i]='B';
            else
                state[i]='A';

            dfs(i);
        }

    //

    cout<<state.substr(1,n);

    cout<<"\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin>>t;

    while(t--)
        solve();

    return 0;
}