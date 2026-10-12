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
