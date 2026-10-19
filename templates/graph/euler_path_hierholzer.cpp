// euler path / circuit (hierholzer, iterative, O(n + m)), multi-edges and self loops ok
// eulerPath(n, edges, directed, start): vertex sequence using every edge once, or {} if impossible
// start = -1 picks a valid start automatically (odd vertex / out-in = 1, else any vertex with an edge)
// for a circuit check path.front() == path.back()
vi eulerPath(int n, const vpi &edges, bool directed, int start = -1)
{
    int m = edges.size();
    vector<vpi> g(n);
    vi deg(n, 0), in(n, 0);
    rep(i, 0, m)
    {
        int u = edges[i].first, v = edges[i].second;
        g[u].pb({v, i}), deg[u]++, in[v]++;
        if (!directed) g[v].pb({u, i}), deg[v]++;
    }
    if (start == -1)
    {
        rep(v, 0, n) if (deg[v]) { start = v; break; }
        if (start == -1) return {0};
        rep(v, 0, n)
        {
            if (directed && deg[v] - in[v] == 1) { start = v; break; }
            if (!directed && deg[v] % 2) { start = v; break; }
        }
    }
    // degree conditions
    int bad = 0;
    rep(v, 0, n)
    {
        int d = directed ? deg[v] - in[v] : deg[v] % 2;
        if (directed && d != 0 && !((d == 1 && v == start) || d == -1)) bad++;
        if (directed && (d > 1 || d < -1)) bad++;
        if (!directed && d && v != start) bad++;
    }
    if (directed ? bad > 0 : bad > 1) return {};
    if (!directed && bad == 1 && deg[start] % 2 == 0) return {};
    vector<char> used(m, 0);
    vi it(n, 0), st = {start}, path;
    while (!st.empty())
    {
        int v = st.back();
        while (it[v] < (int)g[v].size() && used[g[v][it[v]].second]) it[v]++;
        if (it[v] == (int)g[v].size()) { path.pb(v); st.pop_back(); continue; }
        auto e = g[v][it[v]++];
        used[e.second] = 1;
        st.pb(e.first);
    }
    reverse(all(path));
    if ((int)path.size() != m + 1) return {}; // disconnected edges
    return path;
}
