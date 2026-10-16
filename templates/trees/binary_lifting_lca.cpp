const int LOG = 20;
vvi up;
vi depth;

void build_lca(const vvi &g, int root)
{
    int n = g.size();
    up.assign(n, vi(LOG, root));
    depth.assign(n, 0);
    vector<char> vis(n, 0);
    vi st = {root};
    vis[root] = 1;
    while (!st.empty())
    {
        int u = st.back();
        st.pop_back();
        for (int v : g[u])
        {
            if (vis[v]) continue;
            vis[v] = 1;
            up[v][0] = u; //2^0 th ancestor = parent
            depth[v] = depth[u] + 1;
            rep(j, 1, LOG) up[v][j] = up[up[v][j - 1]][j - 1];
            st.pb(v);
        }
    }
}

int kth_ancestor(int u, int k)
{
    if (k > depth[u]) return -1;
    rep(j, 0, LOG) if (k >> j & 1) u = up[u][j]; //19 = 16+2+1
    return u;
}

int get_lca(int u, int v)
{
    if (depth[u] < depth[v]) swap(u, v);
    u = kth_ancestor(u, depth[u] - depth[v]);
    if (u == v) return v; //v is the parent of u, so lca(u,v)=v
    for (int j = LOG - 1; j >= 0; j--)
    {
        if (up[u][j] != up[v][j]) //those ancestors are not the same, so below the lca
        {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0]; //now they are just below lca
}

int dist(int u, int v)
{
    return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
}

/*
void solve()
{
    int n;
    cin >> n;
    vvi g(n + 1);
    rep(i, 0, n - 1)
    {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    build_lca(g, 1);
    int q;
    cin >> q;
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        cout << get_lca(u, v) << nl;
    }
}
*/
