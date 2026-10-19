// vertex biconnected components (blocks), handles multi-edges. BCC b(n); b.add(u, v); b.run();
// b.comps[i] = list of edge ids in block i; b.isCut[v]. isolated vertices belong to no block.
// recursive dfs: fine for n up to ~2e5 on most judges
struct BCC
{
    int n, m = 0, timer = 0;
    vector<vpi> g; // {to, edge id}
    vi tin, low, isCut, st;
    vvi comps;
    vpi edges;
    BCC(int n) : n(n), g(n) {}
    void add(int u, int v) { g[u].pb({v, m}), g[v].pb({u, m}), edges.pb({u, v}), m++; }
    void dfs(int v, int pe)
    {
        tin[v] = low[v] = timer++;
        int kids = 0;
        for (auto &e : g[v])
        {
            int to = e.first, id = e.second;
            if (id == pe) continue;
            if (tin[to] != -1)
            {
                if (tin[to] < tin[v]) st.pb(id); // back edge, push once
                low[v] = min(low[v], tin[to]);
                continue;
            }
            st.pb(id);
            dfs(to, id);
            kids++;
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v])
            {
                if (pe != -1) isCut[v] = 1;
                vi comp;
                while (true)
                {
                    int x = st.back(); st.pop_back();
                    comp.pb(x);
                    if (x == id) break;
                }
                comps.pb(comp);
            }
        }
        if (pe == -1 && kids > 1) isCut[v] = 1;
    }
    void run()
    {
        tin.assign(n, -1), low.assign(n, 0), isCut.assign(n, 0);
        rep(v, 0, n) if (tin[v] == -1) dfs(v, -1);
    }
};
