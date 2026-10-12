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
