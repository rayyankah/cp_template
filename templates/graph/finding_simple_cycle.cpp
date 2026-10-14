// FINDING ONE SIMPLE CYCLE
// findCycle(g, directed) -> vertices of one simple cycle in order, or {-1} if there is none.
//   g        : adjacency list, 0- or 1-indexed (unused vertices are fine)
//   directed : false -> g holds each undirected edge in both lists (u in g[v] and v in g[u])
//              true  -> g[u] holds v for every edge u -> v
// Handles self loops ({u}), multiple edges (undirected u-v twice -> {u, v}),
// disconnected graphs. Iterative dfs, so no stack overflow. O(n + m).
//
// The cycle is returned without repeating the first vertex:
// {a, b, c} means a - b - c - a (directed: a -> b -> c -> a).

vi findCycle(const vvi &g, bool directed)
{
    int n = g.size();
    vi state(n, 0), par(n, -1), it(n, 0);
    // undirected: skip the edge back to the parent only ONCE, so a second parallel edge still counts
    vector<char> skipped(n, 0);
    auto build = [&](int from, int to) // from is a descendant of to (or equal): walk parents
    {
        vi cyc;
        for (int v = from; v != to; v = par[v]) cyc.pb(v);
        cyc.pb(to);
        reverse(all(cyc)); // to -> ... -> from, then the closing edge from -> to
        return cyc;
    };
    rep(s, 0, n)
    {
        if (state[s]) continue;
        vi st = {s};
        state[s] = 1; // 1 = on the dfs stack, 2 = finished
        while (!st.empty())
        {
            int u = st.back();
            if (it[u] == (int)g[u].size())
            {
                state[u] = 2;
                st.pop_back();
                continue;
            }
            int v = g[u][it[u]++];
            if (v == u) return {u}; // self loop
            if (!directed && v == par[u] && !skipped[u])
            {
                skipped[u] = 1; // the tree edge itself, used once
                continue;
            }
            if (state[v] == 0)
            {
                state[v] = 1, par[v] = u;
                st.pb(v);
            }
            else if (state[v] == 1) return build(u, v); // back edge to a vertex on the stack
            // state 2: undirected -> already seen from the other side; directed -> cross/forward edge
        }
    }
    return {-1};
}

/*
void solve()
{
    int n, m;
    cin >> n >> m;
    vvi g(n + 1);
    rep(i, 0, m)
    {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u); // remove this line for a directed graph
    }
    vi cyc = findCycle(g, false);
    if (cyc[0] == -1) { cout << "IMPOSSIBLE" << nl; return; }
    cout << cyc.size() + 1 << nl;
    for (int v : cyc) cout << v << " ";
    cout << cyc[0] << nl;
}
*/
