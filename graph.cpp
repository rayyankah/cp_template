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







//remove k edges and minimize the maximum component size
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;
int n, K;
vector<int> adj[MAXN];
int cuts;

// DFS: returns size of the component containing `u` after optimal cuts inside u's subtree
int dfs_greedy(int u, int p, int S) {
    vector<int> child_sz;
    for (int v : adj[u]) {
        if (v == p) continue;
        child_sz.push_back(dfs_greedy(v, u, S));
    }
    // sort ascending: attach small child components first
    sort(child_sz.begin(), child_sz.end());
    int curr = 1; // count node u itself
    for (int sz : child_sz) {
        // If child's component size > S it means even after internal cuts child's component > S.
        // But this should not happen because children themselves cut internally until each returned component <= S.
        // Still, as a guard:
        if (sz > S) {
            // We must cut the edge to this child (it remains as separate component(s) handled below)
            cuts++;
            continue;
        }
        if (curr + sz <= S) {
            curr += sz; // attach this child's component
        } else {
            // cannot attach -> cut the edge
            cuts++;
        }
    }
    return curr;
}

bool can_with_maxS(int S) {
    cuts = 0;
    dfs_greedy(1, -1, S);
    return cuts <= K;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> K)) return 0;
    for (int i = 1; i <= n; ++i) adj[i].clear();
    for (int i = 0; i < n - 1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // binary search for minimal S in [1..n]
    int lo = 1, hi = n, ans = n;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (can_with_maxS(mid)) {
            ans = mid;
            hi = mid - 1;
        } else lo = mid + 1;
    }

    cout << ans << '\n';
    return 0;
}






