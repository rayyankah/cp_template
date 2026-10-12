//cf - bertown road
#include <bits/stdc++.h>

using namespace std;
#define int long long
const int inf = 1e18;

struct Bridge {
    vector<vector<int>> adj, tree, Components;
    vector<int> low, vis, depth, stack, id;
    int n;
    vector<pair<int, int>> bridge;

    Bridge(int n, vector<vector<int>> &adj) :
            adj(adj), n(n), depth(n + 1), id(n + 1), vis(n + 1), low(n + 1, inf) {
        build();
    };

    void dfs(int u, int p) {
        stack.emplace_back(u);
        low[u] = depth[u];
        vis[u] = 1;
        for (auto v: adj[u]) {
            if (v == p)continue;
            if (vis[v]) {
                low[u] = min(low[u], depth[v]);
                continue;
            }
            depth[v] = depth[u] + 1;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > depth[u])
                bridge.emplace_back(u, v);
        }
        if (low[u] == depth[u]) {
            vector<int> comp;
            while (stack.back() != u)
                comp.emplace_back(stack.back()), stack.pop_back();
            comp.emplace_back(stack.back());
            stack.pop_back();
            Components.emplace_back(comp);
            for (auto v: comp)
                id[v] = Components.size();
        }
    }

    void build() {
        for (int i = 1; i <= n; ++i)
            if (!vis[i])
                dfs(i, 0);

        tree.assign(Components.size() + 1, {});
        for (int u = 1; u <= n; ++u) {
            for (auto v: adj[u]) {
                if (id[u] != id[v])
                    tree[id[u]].emplace_back(id[v]);
            }
        }
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    Bridge T(n, adj);
    if (T.bridge.size())
        return void(cout << "0\n");

    vector<int> vis(n + 1), depth(n + 1);
    function<void(int , int )> dfs = [&](int u , int p) {
        vis[u] = 1;
        for (auto v: adj[u]) {
            if(v == p)continue;
            if (!vis[v]) {
                cout << u << ' ' << v << '\n';
                depth[v] = depth[u] + 1;
                dfs(v , u);
            } else if (depth[v] < depth[u])
                cout << u << ' ' << v << '\n';
        }
    };

    dfs(1 , 0);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef HALZOOM
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif

    int test = 1;
//    cin >> test;

    for (int i = 1; i <= test; ++i) {
        solve();
    }
    return 0;
}
