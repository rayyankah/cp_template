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

// ================= Vertex-biconnected components (blocks) =================
vi tin_bcc, low_bcc;
int timer_bcc;
vector<pair<int,int>> edgeStack;
vector<vector<int>> blocks; // list of blocks, each block is a list of vertices
vector<int> isArt; // 1 if articulation point

void dfs_bcc(int u, int p) {
    tin_bcc[u] = low_bcc[u] = ++timer_bcc;
    int children = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (!tin_bcc[v]) {
            // tree edge
            edgeStack.emplace_back(u,v);
            ++children;
            dfs_bcc(v, u);
            low_bcc[u] = min(low_bcc[u], low_bcc[v]);

            if (low_bcc[v] >= tin_bcc[u]) {
                // u is articulation for this block (unless u is root handled below)
                if (p != -1) isArt[u] = 1;
                // pop edges until (u,v) included
                vector<int> blockVertices;
                while (!edgeStack.empty()) {
                    auto e = edgeStack.back(); edgeStack.pop_back();
                    blockVertices.push_back(e.first);
                    blockVertices.push_back(e.second);
                    if (e.first==u && e.second==v) break;
                }
                // deduplicate vertices in block
                sort(blockVertices.begin(), blockVertices.end());
                blockVertices.erase(unique(blockVertices.begin(), blockVertices.end()), blockVertices.end());
                blocks.push_back(blockVertices);
            }
        } else if (tin_bcc[v] < tin_bcc[u]) {
            // back edge to ancestor; push once
            edgeStack.emplace_back(u,v);
            low_bcc[u] = min(low_bcc[u], tin_bcc[v]);
        }
    }
    if (p == -1 && children > 1) isArt[u] = 1;
}

int solve_min_edges_remove_articulation() {
    // run biconnected algorithm
    tin_bcc.assign(n+1, 0);
    low_bcc.assign(n+1, 0);
    isArt.assign(n+1, 0);
    timer_bcc = 0;
    edgeStack.clear();
    blocks.clear();

    for (int i=1;i<=n;i++) {
        if (!tin_bcc[i]) {
            dfs_bcc(i, -1);
            // after finishing a connected component, there might remain edges (a single block)
            if (!edgeStack.empty()) {
                vector<int> blockVertices;
                while (!edgeStack.empty()) {
                    auto e = edgeStack.back(); edgeStack.pop_back();
                    blockVertices.push_back(e.first);
                    blockVertices.push_back(e.second);
                }
                sort(blockVertices.begin(), blockVertices.end());
                blockVertices.erase(unique(blockVertices.begin(), blockVertices.end()), blockVertices.end());
                blocks.push_back(blockVertices);
            }
        }
    }

    if (blocks.empty()) return 0; // no edges at all (all isolated vertices) -> 0

    // For each block compute how many articulation points it contains
    int B = (int)blocks.size();
    vi degBlock(B, 0);
    vi connOfBlock(B, 0); // which original connected component the block belongs to

    for (int i=0;i<B;i++) {
        int connIdForThisBlock = 0;
        for (int v: blocks[i]) {
            if (isArt[v]) degBlock[i]++;
            if (connIdForThisBlock==0) connIdForThisBlock = compOfNode[v];
        }
        connOfBlock[i] = connIdForThisBlock;
    }

    // group blocks by original connected component
    unordered_map<int, vector<int>> blocksByConn;
    blocksByConn.reserve(B*2);
    for (int i=0;i<B;i++) blocksByConn[connOfBlock[i]].push_back(i);

    int answer = 0;
    for (auto &pr : blocksByConn) {
        auto &vec = pr.second;
        if (vec.size() == 1) continue; // single block => already biconnected inside that connected component
        int leaves = 0;
        for (int idx : vec) if (degBlock[idx] == 1) ++leaves;
        if (leaves == 0) continue;
        answer += (leaves + 1) / 2;
    }
    return answer;
}

// ================= Example driver (read graph, run both) =================
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // read n, m
    if (!(cin >> n >> m)) return 0;
    adj.assign(n+1, {});
    for (int i=0;i<m;i++){
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // mark original connected components (used later)
    mark_connected_components();

    int edges_to_fix_bridges = solve_min_edges_remove_bridges();
    int edges_to_fix_articulation = solve_min_edges_remove_articulation();

    cout << "min edges to add to remove ALL bridges (make 2-edge-connected): " << edges_to_fix_bridges << "\n";
    cout << "min edges to add to remove ALL articulation points (make biconnected): " << edges_to_fix_articulation << "\n";

    return 0;
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





