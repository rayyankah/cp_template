// bridges + articulation points + 2-edge-connected components (handles multi-edges and self loops)
// LowLink L(n); L.add(u, v) for every undirected edge; L.run();
// L.isBridge[edge id], L.isCut[v], L.comp2e[v] = 2-edge-connected component id (bridge tree: join comps by bridges)
// iterative dfs, no stack overflow
struct LowLink
{
    int n, m = 0;
    vector<vpi> g; // {to, edge id}
    vi tin, low, isCut, comp2e;
    vector<char> isBridge;
    vpi edges;
    LowLink(int n) : n(n), g(n) {}
    void add(int u, int v) { g[u].pb({v, m}), g[v].pb({u, m}), edges.pb({u, v}), m++; }
    void run()
    {
        tin.assign(n, -1), low.assign(n, 0), isCut.assign(n, 0), isBridge.assign(m, 0);
        int timer = 0;
        vi it(n, 0), pe(n, -1), kids(n, 0);
        rep(s, 0, n)
        {
            if (tin[s] != -1) continue;
            vi st = {s};
            tin[s] = low[s] = timer++;
            while (!st.empty())
            {
                int v = st.back();
                if (it[v] < (int)g[v].size())
                {
                    int to = g[v][it[v]].first, id = g[v][it[v]].second;
                    it[v]++;
                    if (id == pe[v]) continue; // skip only the edge we came by
                    if (tin[to] != -1) low[v] = min(low[v], tin[to]);
                    else
                    {
                        pe[to] = id, kids[v]++;
                        tin[to] = low[to] = timer++;
                        st.pb(to);
                    }
                }
                else
                {
                    st.pop_back();
                    if (!st.empty())
                    {
                        int p = st.back();
                        low[p] = min(low[p], low[v]);
                        if (low[v] > tin[p]) isBridge[pe[v]] = 1;
                        if (low[v] >= tin[p] && pe[p] != -1) isCut[p] = 1;
                    }
                }
            }
            if (kids[s] > 1) isCut[s] = 1;
        }
        comp2e.assign(n, -1);
        int c = 0;
        rep(s, 0, n)
        {
            if (comp2e[s] != -1) continue;
            vi st = {s};
            comp2e[s] = c;
            while (!st.empty())
            {
                int v = st.back(); st.pop_back();
                for (auto &e : g[v])
                    if (!isBridge[e.second] && comp2e[e.first] == -1) comp2e[e.first] = c, st.pb(e.first);
            }
            c++;
        }
    }
};
