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
