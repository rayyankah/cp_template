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





//finding bridge:const int maxN = 1e5 + 10;
vi adj[maxN];
int vis[maxN], in[maxN], low[maxN];
int timer;//initialized to 0
void dfs(int node, int parent){
    vis[node]=1;
    in[node]=low[node]=timer++;//initialize in and low time to itself first
    for(int child: adj[node]){
        if(child==parent)continue;
        if(vis[child]==1){
            //back edge
            low[node]=min(low[node],in[child]);
        }
        else{
            //forward edge
            dfs(child,node);
            if(low[child]>in[node]){
                //there is no other path to reach child or its descendants
                cout<<"ahare ! "<<node<<" - "<<child<<" is a bridge"<<nl;
            }
            //try to minimize low time of parent using child low time
            low[node]=min(low[node],low[child]);
            
        }
    }
}

//articulation points
const int maxN = 1e5 + 10;
vi adj[maxN];
si articulation_points;
int vis[maxN], in[maxN], low[maxN];
int timer;//initialized to 0
void dfs(int node, int parent=-1){
    vis[node]=1;
    in[node]=low[node]=timer++;
    int children =0;
    for(int &child: adj[node]){
        if(child==parent)continue;
        if(vis[child]){
            //back edge
            low[node]=min(low[node],in[child]);
        }
        else{
            //forward edge
            dfs(child,node);
            if(low[child]>=in[node] && parent!=-1){
                //articulation point
                //root node is handled separately
                articulation_points.insert(node);
            }
            low[node]=min(low[node],low[child]);
            children++;
        }
    }
    if(parent==-1 && children>1){
        articulation_points.insert(node);
        //root node is an articulation point if it has more than 1 child
        //set is used to avoid duplicates
    }

}





//finding bi connected componenets... 
const int maxN = 1e5 + 10;
vi adj[maxN];
si articulation_points;
int vis[maxN], in[maxN], low[maxN];
int timer; // initialized in solve
vector<vector<pair<int, int>>> bcc;
stack<pi> st;

void dfs(int node, int parent = -1)
{
    vis[node] = 1;
    in[node] = low[node] = ++timer;   
    int children = 0;
    for (int &child : adj[node])
    {
        if (child == parent)
            continue;
        if (vis[child])
        {
            // back edge to an ancestor: push when it's an ancestor (in[child] < in[node])
            if (in[child] < in[node]) {
                st.push({node, child});
            }
            low[node] = min(low[node], in[child]);
        }
        else
        {
            // forward (tree) edge
            st.push({node, child});
            dfs(child, node);
            if (low[child] >= in[node] || parent == -1)
            {
                vpi curr_bcc;
                while (!st.empty() && st.top() != make_pair(node, child) && st.top() != make_pair(child, node))
                {
                    curr_bcc.push_back(st.top());
                    st.pop();
                }
                if (!st.empty()) {
                    curr_bcc.push_back(st.top());
                    st.pop();
                }
                bcc.push_back(curr_bcc);
            }

            low[node] = min(low[node], low[child]);
            children++;
        }
    }
    if (parent == -1 && children > 1)
    {
        articulation_points.insert(node);
    }
}

//================ Code starts here ================
void solve()
{
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
        vis[i] = 0;
        in[i] = low[i] = 0;
    }
    while (!st.empty()) st.pop();
    bcc.clear();
    articulation_points.clear();
    timer = 0;

    while (m--)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            dfs(i);
            vpi curr_bcc;
            while (!st.empty())
            {
                curr_bcc.push_back(st.top());
                st.pop();
            }
            if (!curr_bcc.empty())
                bcc.push_back(curr_bcc);
        }
    }
    cout << "bcc are:" << '\n';
    for (auto &component : bcc)
    {
        for (auto &edge : component)
        {
            cout << edge.first << "-" << edge.second << ", ";
        }
        cout << '\n';
    }
}

//================ Code starts here ================
void solve()
{
    int n, m;
    cin >> n >> m;
    while (m--)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            dfs(i);
            vpi curr_bcc;
            while (!st.empty())
            {
                curr_bcc.pb(st.top());
                st.pop();
            }
            if (!curr_bcc.empty())
                bcc.pb(curr_bcc);
            
        }
    }
    cout << "bcc are:" << nl;
    for (auto &component : bcc)
    {
        for (auto &edge : component)
        {
            cout << edge.first << "-" << edge.second << ", ";
        }
        cout << nl;
    }
}




//how many edges to add to make graph safe: 
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;

const int MAXN = 100000 + 5;

// ---------- Input graph ----------
int n, m;
vvi adj;

// ---------- Helpers for connected components (simple DFS) ----------
vi compOfNode; // which original connected component (1..ccount)
void mark_connected_components() {
    compOfNode.assign(n+1, 0);
    int cid = 0;
    vector<int> st;
    for (int s = 1; s <= n; ++s) {
        if (compOfNode[s]) continue;
        ++cid;
        st.clear();
        st.push_back(s);
        compOfNode[s] = cid;
        for (size_t i=0;i<st.size();++i) {
            int u = st[i];
            for (int v: adj[u]) if (!compOfNode[v]) {
                compOfNode[v] = cid;
                st.push_back(v);
            }
        }
    }
}

// ================= Bridges & 2-edge-connected components =================
vi tin_br, low_br;
int timer_br;
vector<pair<int,int>> bridges; // list of bridges (u,v) with u<v always

void dfs_bridges(int u, int p) {
    tin_br[u] = low_br[u] = ++timer_br;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (tin_br[v]) {
            // back edge
            low_br[u] = min(low_br[u], tin_br[v]);
        } else {
            dfs_bridges(v, u);
            low_br[u] = min(low_br[u], low_br[v]);
            if (low_br[v] > tin_br[u]) {
                int a = u, b = v;
                if (a > b) swap(a,b);
                bridges.emplace_back(a,b);
            }
        }
    }
}

// build 2-edge-connected components by skipping bridges
vi comp2edge; // component id (1..k) for each node
unordered_set<long long> bridgeSet;
long long keyPair(int a, int b){ if (a>b) swap(a,b); return ( (long long)a<<32) | (unsigned long long)b; }

void build_bridge_set() {
    bridgeSet.clear();
    for (auto &e: bridges) bridgeSet.insert(keyPair(e.first,e.second));
}

void dfs_assign_comp2edge(int u, int cid) {
    comp2edge[u] = cid;
    for (int v: adj[u]) {
        if (comp2edge[v]) continue;
        if (bridgeSet.count(keyPair(u,v))) continue; // skip bridge edges
        dfs_assign_comp2edge(v, cid);
    }
}

int solve_min_edges_remove_bridges() {
    // run Tarjan to collect bridges
    tin_br.assign(n+1,0);
    low_br.assign(n+1,0);
    timer_br = 0;
    bridges.clear();
    for (int i=1;i<=n;i++) if (!tin_br[i]) dfs_bridges(i, -1);

    // prepare set for quick check
    build_bridge_set();

    // assign 2-edge components
    comp2edge.assign(n+1, 0);
    int cid = 0;
    for (int i=1;i<=n;i++) if (!comp2edge[i]) {
        ++cid;
        dfs_assign_comp2edge(i, cid);
    }

    if (cid == 1) return 0; // already no bridges (single component collapsed)

    // compute degree in bridge-tree
    vi deg(cid+1, 0);
    for (auto &e: bridges) {
        int u = e.first, v = e.second;
        int cu = comp2edge[u], cv = comp2edge[v];
        if (cu==cv) continue;
        deg[cu]++; deg[cv]++;
    }

    // the bridge-tree can be a forest: count leaves per original connected component
    // group components by original connected component (compOfNode)
    map<int, vi> compsByConn; // connId -> list of comp2edge ids
    for (int v = 1; v<=n; ++v) {
        int conn = compOfNode[v];
        int c = comp2edge[v];
        // ensure only push unique comp id once per conn mapping
        // use last element check to avoid duplicates (cheaper)
        if (compsByConn[conn].empty() || compsByConn[conn].back()!=c)
            compsByConn[conn].push_back(c);
    }

    int answer = 0;
    for (auto &pr: compsByConn) {
        auto &vec = pr.second;
        // unique them (because above approach might have duplicates across visitation)
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        if (vec.size() == 1) continue; // a single contracted node -> already no bridges in that original connected comp
        int leaves = 0;
        for (int compId : vec) if (deg[compId] == 1) ++leaves;
        if (leaves==0) continue;
        answer += (leaves + 1) / 2;
    }
    return answer;
}



// finding eulerian path/circuit
const int MAXN = 100005;
int deg[MAXN];
bool hasEulerPath(int n) {
    int odd = 0;
    for (int i = 0; i <= n; ++i) if (deg[i] & 1) ++odd;
    return (odd == 0 || odd == 2);
}

// Hierholzer: recursive removal using multiset adjacency
void findEulerPathOrCircuit(int u, vector<int> &res, vector<multiset<int>> &adj) {
    while (!adj[u].empty()) {
        int v = *adj[u].begin();
        // remove edge u-v from both sides
        adj[u].erase(adj[u].begin());
        auto it = adj[v].find(u);
        if (it != adj[v].end()) adj[v].erase(it);
        findEulerPathOrCircuit(v, res, adj);
    }
    res.push_back(u);
}

//================ Code starts here ================
void solve()
{
     int n, m;
    cin >>n>>m;
    
    // reset degree array for safety (in case of multiple runs)
    for (int i = 1; i <= n; ++i) deg[i] = 0;
    
    vector<pair<int,int>> edges;
    edges.reserve(m);
    vector<multiset<int>> adjm(n + 1);
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edges.emplace_back(u, v);
        adjm[u].insert(v);
        adjm[v].insert(u);
        ++deg[u];
        ++deg[v];
    }

    if (m == 0) {
        cout << "NO\n";
        return;
    }
    
    if (!hasEulerPath(n)) {
        cout << "NO\n";
        return;
    }
    
    // find start vertex: first vertex with odd degree if any, otherwise any vertex with degree > 0
    int start = -1;
    for (int i = 0; i <= n; ++i) {
        if (deg[i] & 1) { start = i; break; }
    }
    if (start == -1) {
        for (int i = 0; i <= n; ++i) if (deg[i] > 0) { start = i; break; }
    }
    if (start == -1) { // no vertex with degree > 0 but m>0 shouldn't happen
        cout << "NO\n";
        return;
    }
    
   
    vector<int> ans;
    findEulerPathOrCircuit(start, ans, adjm);
    reverse(ans.begin(), ans.end());
    
    // Validate: Euler path/circuit must use exactly all edges -> path length == m + 1
    if ((int)ans.size() != m + 1) {
        cout << "NO\n";
        return;
    }

    for (int i = 0; i <= n; ++i) {
        if (!adjm[i].empty()) {
            cout << "NO\n";
            return;
        }
    }
    
    // OK: print path
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return;

}








//n words so that consec words are same on first and last(dominos)
#include <bits/stdc++.h>
using namespace std;

const int ALPH = 26;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; ++i) cin >> words[i];

    // adjacency: for each letter store list of edge ids (edges going out)
    vector<vector<int>> adj(ALPH);
    vector<int> indeg(ALPH,0), outdeg(ALPH,0);
    vector<int> from(n), to(n);

    for (int i = 0; i < n; ++i) {
        int u = words[i].front() - 'a';
        int v = words[i].back() - 'a';
        from[i] = u; to[i] = v;
        adj[u].push_back(i);
        outdeg[u]++; indeg[v]++;
    }

    // degree conditions for directed Euler path/circuit
    int start = -1;
    int plus = 0, minus = 0;
    for (int i = 0; i < ALPH; ++i) {
        int d = outdeg[i] - indeg[i];
        if (d == 1) { plus++; start = i; }
        else if (d == -1) { minus++; }
        else if (d != 0) { cout << "NO\n"; return 0; }
    }
    if (!((plus == 1 && minus == 1) || (plus == 0 && minus == 0))) {
        cout << "NO\n"; return 0;
    }
    if (start == -1) { // circuit case: pick any vertex with outgoing edge
        for (int i = 0; i < ALPH; ++i) if (outdeg[i] > 0) { start = i; break; }
    }

    // check connectivity on underlying undirected graph (only vertices with deg>0)
    vector<vector<int>> und(ALPH);
    vector<int> has(ALPH,0);
    for (int e = 0; e < n; ++e) {
        int u = from[e], v = to[e];
        und[u].push_back(v);
        und[v].push_back(u);
        has[u] = has[v] = 1;
    }
    // find any vertex with has==1 as root
    int root = -1;
    for (int i=0;i<ALPH;i++) if (has[i]) { root = i; break; }
    if (root != -1) {
        vector<int> vis(ALPH,0);
        stack<int> st; st.push(root); vis[root]=1;
        int cnt=0;
        while(!st.empty()){
            int v = st.top(); st.pop(); ++cnt;
            for(int nb: und[v]) if(!vis[nb]) { vis[nb]=1; st.push(nb); }
        }
        int totalHas = 0;
        for(int i=0;i<ALPH;i++) if(has[i]) totalHas++;
        if (cnt != totalHas) { cout << "NO\n"; return 0; }
    }

    // Hierholzer recursive (minimal-change style)
    vector<int> used(n, 0);
    vector<int> path_edges; path_edges.reserve(n);

    // We will pop from the back of adj[u] to simulate removing edges (fast).
    // If adjacency vector originally ordered differently, doesn't matter.
    function<void(int)> findEuler = [&](int u) {
        while (!adj[u].empty()) {
            int eid = adj[u].back();
            adj[u].pop_back();               // remove that outgoing edge
            if (used[eid]) continue;         // if already used (shouldn't normally happen)
            used[eid] = 1;
            int v = to[eid];
            findEuler(v);
            path_edges.push_back(eid);       // record edge when backtracking
        }
    };

    findEuler(start);

    if ((int)path_edges.size() != n) {
        // not all edges used -> impossible (shouldn't if connectivity + degree ok, but safe)
        cout << "NO\n";
        return 0;
    }

    reverse(path_edges.begin(), path_edges.end());
    // print words in found order (minimal format: space separated)
    for (int i = 0; i < (int)path_edges.size(); ++i) {
        if (i) cout << ' ';
        cout << words[path_edges[i]];
    }
    cout << '\n';
    return 0;
}







//GRAPH COLORING
void solve()
{
    int n, m;
    cin >> n >> m;
    vi adj[n + 1];
    rep(i, 1, m + 1)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vi colors(n + 1, 0);
    function<void(int)> dfs = [&](int node)
    {
        // this node is visited and assigned a color
        for (int child : adj[node])
        {
            if (colors[child] == 0)
            {
                // unvisited child,assigning a color
                colors[child] = colors[node] == 1 ? 2 : 1;
                // dfs chalabe ke???
                dfs(child);
            }

            // visited and ancestor
            else
            {
                if (colors[child] + colors[node] != 3)
                {
                    cout << "IMPOSSIBLE" << nl;
                    exit(0);
                }
            }
        }
    };
    rep(i, 1, n + 1)
    {
        if (colors[i] == 0)
        {
            // unvisited so is not assigned color
            colors[i] = 1;
            dfs(i);
        }
    }
    rep(i, 1, n + 1)
    {
        cout << colors[i] << " ";
    }
    cout << nl;
}









//uva = tourist guide..


signed main()
{
    fast;

    int kase = 1;
    while (true)
    {
        int n, r;
        cin >> n >> r;
        if (n == 0 && r == 0)
            break;
        vv<int> matrix(n + 1, v<int>(n + 1, 0));
        for (int i = 0; i < r; i++)
        {
            int c1, c2, p;
            cin >> c1 >> c2 >> p;
            matrix[c1][c2] = p;
            matrix[c2][c1] = p;
        }
        int s, d, t;
        cin >> s >> d >> t;
        // floyd warshall for max min capacity
        for (int k = 1; k <= n; k++)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    matrix[i][j] = max(matrix[i][j], min(matrix[i][k], matrix[k][j]));
                }
            }
        }
        int cap = matrix[s][d];
        int denom = cap - 1;
        int trips = t / denom;
        if (t % denom != 0)
            trips++;
        cout << "Scenario #" << kase << nl;
        cout << "Minimum Number of Trips = " << trips << nl;
        cout << nl;
        kase++;
    }
}












//uva -network
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define oo 1000
int link[100][100], n;
int depth[100], low[100];
int used[100], cut;
int DFS(int node, int d, int parent) {
 int i, back = oo, son = 0, tmp, flag = 0;
 depth[node] = d;
 for(i = 1; i <= n; i++) {
  if(link[node][i] == 1) {
   if(used[i] == 0) {
    used[i] = 1;
    tmp = DFS(i, d+1, node);
    if(tmp >= d) flag = 1;
    back = back < tmp ? back : tmp;
    son++;
   } else {
    if(i != parent)
     back = back < depth[i] ? back : depth[i];
   }
  }
 }
 low[node] = back;
 if(node == 1) {
  if(son > 1)
   cut++;
 } else {
  cut += flag;
 }
 return low[node];
}
int main() {
 int x, y;
 char c;
 while(scanf("%d", &n) == 1 && n) {
  memset(link, 0, sizeof(link));
  memset(depth, 0, sizeof(depth));
  memset(low, 0, sizeof(low));
  memset(used, 0, sizeof(used));
  while(scanf("%d", &x) == 1 && x) {
   while(scanf("%d%c", &y, &c) == 2) {
    link[x][y] = 1;
    link[y][x] = 1;
    if(c == '\n') break;
   }
  }
  used[1] = 1;
  cut = 0;
  DFS(1, 1, 0);
  printf("%d\n", cut);
 }
    return 0;
}




//online:


//jjzzhu and cities - cf(add new path and if used);
 
//================ Code starts here ================
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vpi> adj(n + 1);
    vector<array<int,3>> roads;
    rep(i, 0, m)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
        roads.pb({u, v, w});
    }
 
    vpi temp;
    rep(i, 0, k)
    {
        int node, dis;
        cin >> node >> dis;
        temp.pb({dis, node});
        // add train edges to graph before Dijkstra
        adj[1].pb({node, dis});
        adj[node].pb({1, dis});
    }
 
    vector<long long> dist(n + 1, LLONG_MAX);
    dist[1] = 0;
    set<pair<long long,int>> s;
    s.insert({0, 1});
    vi visited(n + 1, 0);
    while (!s.empty())
    {
        auto yo = *s.begin();
        s.erase(s.begin());
        int u = yo.second;
        if (visited[u]) continue;
        visited[u] = 1;
        long long d = yo.first;
        for (auto &ele : adj[u])
        {
            int v = ele.first;
            long long wt = ele.second;
            if (!visited[v])
            {
                if (d + wt < dist[v])
                {
                    if (dist[v] != LLONG_MAX) s.erase({dist[v], v});
                    dist[v] = d + wt;
                    s.insert({dist[v], v});
                }
            }
        }
    }
 
    // count how many road-edges give the shortest distance for each node
    vi roadCount(n + 1, 0);
    for (auto &e : roads)
    {
        int u = e[0], v = e[1], w = e[2];
        if (dist[u] != LLONG_MAX && dist[u] + (long long)w == dist[v]) ++roadCount[v];
        if (dist[v] != LLONG_MAX && dist[v] + (long long)w == dist[u]) ++roadCount[u];
    }
 
    // used[node] == true means NO road provides shortest path (so a train must be kept)
    vector<bool> used(n + 1, false);
    for (int i = 1; i <= n; ++i) used[i] = (roadCount[i] == 0);
 
    int ans = 0;
    vi num(n + 1, 0);
    sort(all(temp));
    rep(i, 0, (int)temp.size()){
        int node = temp[i].second;
        int dis = temp[i].first;
        if (dist[node] == dis) num[node]++;
    }
    rep(i, 0, (int)temp.size()){
        int node = temp[i].second;
        int dis = temp[i].first;
        if (dist[node] < dis){
            ans++;
        }
        else if (dist[node] == dis && num[node] > 1 && used[node]){
            ans++;
            num[node]--;
        }
        else if (!used[node] && dist[node] == dis){
            ans++;
        }
    }
 
    cout << ans << nl;
}







//cf- dijkstra?
// ================ Author: Rayyan Khalil ================

#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
using namespace std;

#define vvi vector<vector<int>>
#define vll vector<long long>
#define si set<int>
#define mii map<int, int>
#define vi vector<int>
#define vpi vector<pair<int, int>>
#define pi pair<int, int>
#define ll long long
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define tk_input(a) rep(i, 0, n) cin >> a[i]
#define repb(i, a, b) for (int i = a; i >= b; i--)
#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

#ifdef DEBUG
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_print(__VA_ARGS__)
void debug_print() { cerr << endl; }
template <typename T, typename... Args>
void debug_print(T t, Args... args)
{
    cerr << t;
    if (sizeof...(args))
        cerr << ", ";
    debug_print(args...);
}
#else
#define debug(...)
#endif

#define myCeil(a, b) (a + b - 1) / b
const int MOD = 1000000007;
#define nl '\n'
#define precise(x) fixed << setprecision(x)
#define int ll
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
//rnd()  generates a random number
int binMul(int a, int b, int m)
{
    int res = 0;
    a %= m;
    while (b > 0)
    {
        if (b & 1)
        {
            res = (res + a) % m;
        }
        a = (a + a) % m;
        b >>= 1;
    }
    return res;
}

int binExp(int a, int b)
{
    int res = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            res = (1LL * res * a) % MOD;
        }
        a = (1LL * a * a) % MOD;
        b >>= 1;
    }
    return res;
}
int extended_euclidean_gcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extended_euclidean_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

template <class T>
using vv = vector<vector<T>>;
template <class T>
using v = vector<T>;

// ------------------ SAFE unordered_map helpers ------------------
struct custom_hash
{
    static inline uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const noexcept
    {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return (size_t)splitmix64(x + FIXED_RANDOM);
    }
};

template <class K, class V>
using umap = unordered_map<K, V, custom_hash>;
template <class T>
using uset = unordered_set<T, custom_hash>;

template <class Map>
inline void secure_reserve(Map &m, size_t expected_size, float lf = 0.25f)
{
    m.max_load_factor(lf);
    m.reserve(expected_size);
}

template <class T>
void read(vector<T> &a)
{
    for (auto &x : a)
        cin >> x;
}
template <class T>
void read(vv<T> &a)
{
    for (auto &r : a)
        for (auto &x : r)
            cin >> x;
}

template <class A, class B>
ostream &operator<<(ostream &os, const pair<A, B> &p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &a)
{
    os << "[";
    string s = "";
    for (auto &x : a)
    {
        os << s << x;
        s = ", ";
    }
    os << "]";
    return os;
}
template <class T>
ostream &operator<<(ostream &os, const set<T> &a)
{
    os << "{";
    string s = "";
    for (auto &x : a)
    {
        os << s << x;
        s = ", ";
    }
    os << "}";
    return os;
}
template <class T>
ostream &operator<<(ostream &os, const multiset<T> &a)
{
    os << "{";
    string s = "";
    for (auto &x : a)
    {
        os << s << x;
        s = ", ";
    }
    os << "}";
    return os;
}
template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &a)
{
    os << "{";
    string s = "";
    for (auto &kv : a)
    {
        os << s << kv.first << ": " << kv.second;
        s = ", ";
    }
    os << "}";
    return os;
}

template <class K, class V, class H, class Eq, class Alloc>
ostream &operator<<(ostream &os, const unordered_map<K, V, H, Eq, Alloc> &a)
{
    os << "{";
    string s = "";
    for (auto &kv : a)
    {
        os << s << kv.first << ": " << kv.second;
        s = ", ";
    }
    os << "}";
    return os;
}
template <class T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &a)
{
    os << "[";
    string s = "";
    for (auto &x : a)
    {
        os << s << x;
        s = ", ";
    }
    os << "]";
    return os;
}

// template<typename T>
// using ordered_set = tree<T, null_type, //less<T>, rb_tree_tag, //tree_order_statistics_node_update>;
// ans+=b.size()-b.order_of_key(in[i].second+1);

template <class T>
void debug_print_array(vector<T> &arr)
{
    for (auto &elem : arr)
    {
        cerr << elem << " ";
    }
    cerr << endl;
}
const int N = 1e6 + 10;
vi factorial(N);
vi inv(N);
void compute_factorials()
{
    factorial[0] = 1;
    for (int i = 1; i < N; i++)
    {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    inv[N - 1] = binExp(factorial[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--)
    {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;
    }
}
int ncr(int n, int r)
{
    if (r > n || r < 0)
        return 0;
 
    return (binMul(factorial[n], binMul(inv[r], inv[n - r], MOD), MOD));
}
//random number within a range [l,r]
int rndRange(int l, int r) { return rnd() % (r - l + 1) + l; }


//================ Code starts here ================
void solve()
{
  int n,m;
  cin >>n>>m;
  vector<vector<pi>>adj(n+1);
  rep(i,0,m){
    int u,v,w;
    cin >>u>>v>>w;
    adj[u].pb({v,w});
    adj[v].pb({u,w});
  }
  set<pi>pq;
  vi par(n+1,-1);
  par[1]=0;
  vi dist(n+1,LLONG_MAX);
  dist[1]=0;
  pq.insert({0,1});
  while(!pq.empty()){
    pi v = *pq.begin();
    pq.erase(pq.begin());
    for(auto &ele: adj[v.second]){
        int wt = ele.second;
        if(dist[ele.first]>dist[v.second]+wt){
            dist[ele.first] = dist[v.second]+wt;
            par[ele.first] = v.second;
            pq.insert({dist[ele.first],ele.first});
        }
    }
  }
  if(dist[n]==LLONG_MAX){
    cout<<-1<<nl;
    return;
  }
  vi ans;
  ans.pb(n);
  int now = par[n];
  while(now!=0){
    ans.pb(now);
    now = par[now];
  }
  reverse(all(ans));
  for(auto &ele: ans){
    cout<<ele<<" ";
  }
  cout<<nl;

}

signed main()
{
    fast;

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
}




//a sec online
void solve()
{
    int n, m, k, x;
    cin >> n >> m >> k >> x;
    vi a(k + 1);
    vi h(k + 1);
    rep(i, 1, k + 1)
    {
        cin >> a[i];
    }
    rep(i, 1, k + 1)
    {
        cin >> h[i];
    }
    vector<vector<pi>> dist(n + 1, vpi(n + 1));
    int INF = LLONG_MAX;
    rep(i, 1, n + 1)
    {
        rep(j, 1, n + 1)
        {
            dist[i][j] = {INF, -1};
        }
    }
    rep(i, 1, n + 1)
    {
        dist[i][i].first = 0;
    }
    rep(i, 0, m)
    {
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = {w, u};
        
        dist[v][u] = {w, v};
    }

    rep(kk, 1, n + 1)
    {
        rep(i, 1, n + 1)
        {
            rep(j, 1, n + 1)
            {
                int dd = dist[i][kk].first;
                int dd2 = dist[kk][j].first;
                if (dd != INF && dd2 != INF)
                {
                    if (dist[i][j].first > dd + dd2)
                    {
                        dist[i][j].second = kk;
                        dist[i][j].first = dd + dd2;
                    }
                }
            }
        }
    }
   
    int mincost = INF;
    int tar = -1;
    int minlast = INF;
    rep(i,1,n+1){
        int s =0;
        bool flag = false;
        int mx = -1;
        rep(j,1,k+1){
            int st = a[j];
            if(dist[st][i].first>x){
                flag = true;
                break;
            }
            s+=dist[st][i].first*h[j];
            mx = max<ll>(mx,dist[st][i].first);
            
        }
        if(flag)continue;
        if(s<mincost){
            mincost=s;
            tar=i;
            minlast =mx;
        }
    }
    if(tar==-1){
        cout<<"No meeting"<<nl;
        return;
    }
    cout<<tar<<" "<<mincost<<" "<<minlast<<nl;
    rep(i,1,k+1){
        if(a[i]==tar){
            cout<<a[i]<<" "<<0<<nl;
            continue;
        }
        vi path;
        int now = tar;
        while(true){
            path.pb(now);
            if(now==a[i])break;
            now = dist[a[i]][now].second;
        }
        reverse(all(path));
        rep(i,0,(int)path.size()-1){
            cout<<path[i]<<" -> ";
        }
        cout<<path[(int)path.size()-1]<<" "<<h[i]*dist[a[i]][tar].first<<nl;
    }
    return;
}




// b online
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vi st(n + 1);
    vi tar(n + 1);
    rep(i, 1, n + 1)
    {
        cin >> st[i];
    }
    rep(i, 1, n + 1)
    {
        cin >> tar[i];
    }
    int INF = LLONG_MAX;
    vvi dist(n + 1, vi(n + 1, INF));
    rep(i, 0, m)
    {
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = w;
    }
    rep(i, 1, n + 1)
    {
        dist[i][i] = 0;
    }
    rep(k,1,n+1){
        rep(i,1,n+1){
            rep(j,1,n+1){
                int dd = dist[i][k];
                int dd2 = dist[k][j];
                if(dd!=INF && dd2!=INF){
                    dist[i][j]=min<ll>(dist[i][j],dd+dd2);
                }
            }
        }
    }
    vi ans;
    rep(i,1,n+1){
        if(dist[st[i]][tar[i]]!=INF){
            ans.pb(dist[st[i]][tar[i]]);
        }
    }
    
    sort(all(ans),greater<int>());
    int sz = (int)ans.size();
    int sum =0;
    int i=0;
    int now =0;
    int ct = 0;
    // debug(dist[4][3],st[1],tar[1]);
    while(i<sz){
        int mul = (1<<now);
        sum+=ans[i]*mul;
        ct++;
        if(ct==k){
            ct=0;
            now++;
        }
        i++;
    }
    cout<<sum<<nl;
}



//c online: 
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vi cost(n + 1);
    vi discon(n + 1, 0);
    rep(i, 1, n + 1)
    {
        cin >> cost[i];
    }
    vvi dist(n + 1, vi(n + 1, LLONG_MAX));
    rep(i, 1, n + 1)
    {
        dist[i][i] = 0;
    }
    // cin >> k;
    vector<vpi> adj(n + 1);
    rep(i, 0, m)
    {
        int u, v, w;
        cin >> u >> v >> w;
        if (cost[u] == -1 || cost[v] == -1)
        {
            continue;
        }
        int cst = w;
        adj[u].pb({v, cst});
        dist[u][v] = min<ll>(dist[u][v], cst);
        cst = w;
        adj[v].pb({u, cst});
        dist[v][u] = min<ll>(dist[v][u], cst);
    }
    // int k;
    // cin >>k;

    rep(k, 1, n + 1)
    {
        rep(i, 1, n + 1)
        {
            rep(j, 1, n + 1)
            {
                if (dist[i][k] != LLONG_MAX && dist[k][j] != LLONG_MAX)
                {
                    dist[i][j] = min<ll>(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    vector<vector<pi>> findist(n + 1, vpi(n + 1));
    rep(i, 1, n + 1)
    {
        rep(j, 1, n + 1)
        {
            findist[i][j] = {dist[i][j], j};
        }
    }
    rep(i, 1, n + 1)
    {
        sort(findist[i].begin() + 1, findist[i].end());
    }
    // debug(findist);
    int q;
    cin >> q;
    while (q--)
    {
        int start;
        cin >> start;
        // debug(findist[start]);
        int ct = 0;
        int i = 1;
        vi tempcost = cost;
        while (ct < k && i <= n)
        {
            if (findist[start][i].first == LLONG_MAX)
            {
                cout << -1 << " ";
                ct++;
                continue;
            }
            if (tempcost[findist[start][i].second] == 0)
            {
                i++;
                continue;
            }
            else
            {
                cout << findist[start][i].first << " ";
                ct++;
                tempcost[findist[start][i].second]--;
            }
        }
        while (ct < k)
        {
            cout << -1 << " ";
            ct++;
        }
        cout<<nl;
    }
    return;
}


// tweaks: 

void solve_restricted_intermediate() {
    int n, m, q;
    cin >> n >> m >> q;

    const long long INF = (long long)4e18;
    vector<vector<long long>> dist(n+1, vector<long long>(n+1, INF));
    for(int i=1;i<=n;i++) dist[i][i]=0;

    for(int i=0;i<m;i++){
        int u,v; long long w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }

    // bucket queries by k
    struct Query{int u,v,idx;};
    vector<vector<Query>> bucket(n+1);
    vector<long long> ans(q);

    for(int i=0;i<q;i++){
        int u,v,k; 
        cin >> u >> v >> k;
        if(k<0) k=0;
        if(k>n) k=n;
        bucket[k].push_back({u,v,i});
    }

    // k = 0 answers (no intermediates) means direct edges only (dist already has direct best)
    for(auto &qq: bucket[0]){
        long long d = dist[qq.u][qq.v];
        ans[qq.idx] = (d>=INF/2? -1 : d);
    }

    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            if(dist[i][k]>=INF/2) continue;
            for(int j=1;j<=n;j++){
                if(dist[k][j]>=INF/2) continue;
                long long nd = dist[i][k] + dist[k][j];
                if(nd < dist[i][j]) dist[i][j] = nd;
            }
        }
        for(auto &qq: bucket[k]){
            long long d = dist[qq.u][qq.v];
            ans[qq.idx] = (d>=INF/2? -1 : d);
        }
    }

    for(int i=0;i<q;i++) cout << ans[i] << "\n";
} 

void solve_directed_apsp() {
    int n, m, q;
    cin >> n >> m >> q;

    const long long INF = (long long)4e18;
    vector<vector<long long>> dist(n+1, vector<long long>(n+1, INF));
    for(int i=1;i<=n;i++) dist[i][i]=0;

    for(int i=0;i<m;i++){
        int u,v; long long w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w); // no dist[v][u]
    }

    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++){
            if(dist[i][k]>=INF/2) continue;
            for(int j=1;j<=n;j++){
                if(dist[k][j]>=INF/2) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }

    while(q--){
        int u,v; cin >> u >> v;
        cout << (dist[u][v]>=INF/2? -1 : dist[u][v]) << "\n";
    }
} 


#include <bits/stdc++.h>
using namespace std;

#define vll vector<long long>
#define ll long long

void solve_arbitrage_limit_k() {
    int n;
    cin >> n;

    // Map to assign indices to currency names
    map<string, int> mp;
    for (int i = 1; i <= n; i++) {
        string s; 
        cin >> s;
        mp[s] = i;
    }

    int m; // number of exchange rates
    cin >> m;

    // Initialize exchange rates matrix for maximum product
    vector<vector<long double>> dist(n + 1, vector<long double>(n + 1, -1.0));
    for (int i = 1; i <= n; i++) {
        dist[i][i] = 1.0;  // distance to itself is always 1
    }

    // Read the exchange rates
    for (int i = 0; i < m; i++) {
        string a, b;
        long double r;
        cin >> a >> r >> b;

        int u = mp[a], v = mp[b];
        dist[u][v] = max(dist[u][v], r);  // Set the maximum exchange rate
    }

    int K; // maximum number of exchanges
    cin >> K;

    // Perform the modified Floyd-Warshall with the step limit (max K exchanges)
    vector<vector<vector<long double>>> dp(K + 1, vector<vector<long double>>(n + 1, vector<long double>(n + 1, -1.0)));

    // Base case: with 0 exchanges, the only path is direct exchange (dist[i][j])
    for (int i = 1; i <= n; i++) {
        dp[0][i][i] = 1.0;
    }

    // Initialize the first level of exchanges (single exchange)
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[1][i][j] = dist[i][j];  // Direct exchange rates
        }
    }

    // Apply Floyd-Warshall with up to K exchanges
    for (int k = 2; k <= K; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                for (int intermediate = 1; intermediate <= n; intermediate++) {
                    if (dp[k - 1][i][intermediate] >= 0 && dp[1][intermediate][j] >= 0) {
                        dp[k][i][j] = max(dp[k][i][j], dp[k - 1][i][intermediate] * dp[1][intermediate][j]);
                    }
                }
            }
        }
    }

    // Check for arbitrage: if any diagonal value is > 1.0, arbitrage is possible
    for (int k = 1; k <= K; k++) {
        for (int i = 1; i <= n; i++) {
            if (dp[k][i][i] > 1.0) {
                cout << "Yes\n";
                return;
            }
        }
    }

    cout << "No\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve_arbitrage_limit_k();
    return 0;
}

//normal dijkstra
// ================ Author: Rayyan Khalil ================

#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
using namespace std;

#define vvi vector<vector<int>>
#define vll vector<long long>
#define si set<int>
#define mii map<int, int>
#define vi vector<int>
#define vpi vector<pair<int, int>>
#define pi pair<int, int>
#define ll long long
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define tk_input(a) rep(i, 0, n) cin >> a[i]
#define repb(i, a, b) for (int i = a; i >= b; i--)
#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

#ifdef DEBUG
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_print(__VA_ARGS__)
void debug_print() { cerr << endl; }
template <typename T, typename... Args>
void debug_print(T t, Args... args)
{
    cerr << t;
    if (sizeof...(args))
        cerr << ", ";
    debug_print(args...);
}
#else
#define debug(...)
#endif

#define myCeil(a, b) (a + b - 1) / b
const int MOD = 1000000007;
#define nl '\n'
#define precise(x) fixed << setprecision(x)
#define int ll
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
// rnd()  generates a random number
int binMul(int a, int b, int m)
{
    int res = 0;
    a %= m;
    while (b > 0)
    {
        if (b & 1)
        {
            res = (res + a) % m;
        }
        a = (a + a) % m;
        b >>= 1;
    }
    return res;
}

int binExp(int a, int b)
{
    int res = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            res = (1LL * res * a) % MOD;
        }
        a = (1LL * a * a) % MOD;
        b >>= 1;
    }
    return res;
}
int extended_euclidean_gcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extended_euclidean_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

template <class T>
using vv = vector<vector<T>>;
template <class T>
using v = vector<T>;

// ------------------ SAFE unordered_map helpers ------------------
struct custom_hash
{
    static inline uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const noexcept
    {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return (size_t)splitmix64(x + FIXED_RANDOM);
    }
};

template <class K, class V>
using umap = unordered_map<K, V, custom_hash>;
template <class T>
using uset = unordered_set<T, custom_hash>;

template <class Map>
inline void secure_reserve(Map &m, size_t expected_size, float lf = 0.25f)
{
    m.max_load_factor(lf);
    m.reserve(expected_size);
}

template <class T>
void read(vector<T> &a)
{
    for (auto &x : a)
        cin >> x;
}
template <class T>
void read(vv<T> &a)
{
    for (auto &r : a)
        for (auto &x : r)
            cin >> x;
}

template <class A, class B>
ostream &operator<<(ostream &os, const pair<A, B> &p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &a)
{
    os << "[";
    string s = "";
    for (auto &x : a)
    {
        os << s << x;
        s = ", ";
    }
    os << "]";
    return os;
}
template <class T>
ostream &operator<<(ostream &os, const set<T> &a)
{
    os << "{";
    string s = "";
    for (auto &x : a)
    {
        os << s << x;
        s = ", ";
    }
    os << "}";
    return os;
}
template <class T>
ostream &operator<<(ostream &os, const multiset<T> &a)
{
    os << "{";
    string s = "";
    for (auto &x : a)
    {
        os << s << x;
        s = ", ";
    }
    os << "}";
    return os;
}
template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &a)
{
    os << "{";
    string s = "";
    for (auto &kv : a)
    {
        os << s << kv.first << ": " << kv.second;
        s = ", ";
    }
    os << "}";
    return os;
}

template <class K, class V, class H, class Eq, class Alloc>
ostream &operator<<(ostream &os, const unordered_map<K, V, H, Eq, Alloc> &a)
{
    os << "{";
    string s = "";
    for (auto &kv : a)
    {
        os << s << kv.first << ": " << kv.second;
        s = ", ";
    }
    os << "}";
    return os;
}
template <class T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &a)
{
    os << "[";
    string s = "";
    for (auto &x : a)
    {
        os << s << x;
        s = ", ";
    }
    os << "]";
    return os;
}

// template<typename T>
// using ordered_set = tree<T, null_type, //less<T>, rb_tree_tag, //tree_order_statistics_node_update>;
// ans+=b.size()-b.order_of_key(in[i].second+1);

template <class T>
void debug_print_array(vector<T> &arr)
{
    for (auto &elem : arr)
    {
        cerr << elem << " ";
    }
    cerr << endl;
}
const int N = 1e6 + 10;
vi factorial(N);
vi inv(N);
void compute_factorials()
{
    factorial[0] = 1;
    for (int i = 1; i < N; i++)
    {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    inv[N - 1] = binExp(factorial[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--)
    {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;
    }
}
int ncr(int n, int r)
{
    if (r > n || r < 0)
        return 0;

    return (binMul(factorial[n], binMul(inv[r], inv[n - r], MOD), MOD));
}
// random number within a range [l,r]
int rndRange(int l, int r) { return rnd() % (r - l + 1) + l; }

//================ Code starts here ================
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vpi> adj(n + 1);
    rep(i, 0, m)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({v, w});
        // adj[v].pb({u, w});
    }
    vi dist(n + 1, LLONG_MAX);
    dist[1] = 0;

    set<pi> s;
    s.insert({0, 1});
    vi visited(n + 1, 0);
    while (!s.empty())
    {

        pi vn = *s.begin();

        s.erase(s.begin());
        if (visited[vn.second])
        {
            continue;
        }
        visited[vn.second] = 1;
        for (auto &child : adj[vn.second])
        {
            if (!visited[child.first])
            {
                int wt = child.second;
                int node = child.first;
                int ch = vn.first + child.second;
                if (ch < dist[node])
                {
                    dist[node] = ch;
                    s.insert({ch, node});
                }
            }
        }
    }
    rep(i, 1, n + 1)
    {
        cout << dist[i] << " ";
    }
    cout << nl;
}

signed main()
{
    fast;

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
}
