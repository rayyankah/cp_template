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
