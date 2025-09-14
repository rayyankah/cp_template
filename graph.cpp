//diameter of a tree
#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
vector<int> adj[N];
bool visited[N];
int n;

int farNode, maxDist;

void dfs(int u, int dist) {
    visited[u] = true;
    if (dist > maxDist) {
        maxDist = dist;
        farNode = u;
    }
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, dist + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // First DFS from node 1
    fill(visited, visited + n + 1, false);
    maxDist = -1;
    dfs(1, 0);

    // Second DFS from farNode
    fill(visited, visited + n + 1, false);
    maxDist = -1;
    dfs(farNode, 0);

    int diameter = maxDist;
    int ans = 2 * (n - 1) - diameter;
    cout << ans << "\n";

    return 0;
}




//deleting edge to satisafy D[u] for every u
void solve()
{
  int n,m;
  cin >>n>>m;
  vvi adj(n+1);
  vi deg(n+1, 0);
  vpi edges;
  rep(i,0,m){
    int u,v;
    cin >>u>>v;
    adj[u].pb(v);
    adj[v].pb(u);
    deg[u]++;
    deg[v]++;
    edges.emplace_back(u,v);
  }
  vi D(n+1);
  rep(i,1,n+1){
    cin >>D[i];
  }
  vi need(n+1);
  rep(i,1,n+1){
    need[i] = (deg[i]&1)^D[i];//if we need to change that degree
  }
  vi vis(n+1,0);
  vpi deletions;
  function<void(int,int)> dfs = [&](int u, int p){
    vis[u]=1;
    for(int child: adj[u]){
        if(child==p)continue;
        if(!vis[child]){
            //resolve child first
            dfs(child,u);
            if(need[child]==1){
                deletions.emplace_back(u,child);
                need[child]=0;
                if(need[u]==1){
                    need[u]=0;
                }
                else{
                    need[u]=1;
                }
            }
        }
    }
  };
  rep(i,1,n+1){
    if(!vis[i]){
        dfs(i,0);
        if(need[i]==1){
            cout<<-1<<nl;//impossible if neeed to toggle after resolving whole component
            return;
        }
    }
  }
  cout<<deletions.size()<<nl;
  for(auto &x: deletions){
    cout<<x.first<<" "<<x.second<<nl;
  }
}






