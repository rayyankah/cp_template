// sum of distances over all unordered pairs of a tree: every edge is used by sz * (n - sz) paths
// g = adjacency list (any labels 0..n-1 or 1..n with g.size() = n + 1), root = any vertex. iterative
int sumAllPairDistances(const vvi &g, int root, int n)
{
    vi par(g.size(), -1), order = {root}, sz(g.size(), 1);
    rep(i, 0, (int)order.size())
    {
        int v = order[i];
        for (int u : g[v]) if (u != par[v]) par[u] = v, order.pb(u);
    }
    int res = 0;
    repb(i, (int)order.size() - 1, 1)
    {
        int v = order[i];
        sz[par[v]] += sz[v];
        res += sz[v] * (n - sz[v]);
    }
    return res;
}
