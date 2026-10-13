// dominator tree (lengauer tarjan). dominator d(n); d.add(u, v); vi idom = d.build(root)
// idom[root] = root, unreachable vertices get -1
struct dominator
{
    int n;
    vvi g, rg, bucket;
    vi arr, par, rev, sdom, dom, dsu, lbl;
    int t = 0;
    dominator(int n) : n(n), g(n), rg(n), bucket(n), arr(n, -1), par(n), rev(n), sdom(n), dom(n), dsu(n), lbl(n) {}
    void add(int u, int v) { g[u].pb(v); }
    int find(int u, int x = 0)
    {
        if (u == dsu[u]) return x ? -1 : u;
        int v = find(dsu[u], x + 1);
        if (v < 0) return u;
        if (sdom[lbl[dsu[u]]] < sdom[lbl[u]]) lbl[u] = lbl[dsu[u]];
        dsu[u] = v;
        return x ? v : lbl[u];
    }
    void dfs(int root)
    {
        vpi st = {{root, -1}};
        while (!st.empty())
        {
            int u = st.back().first, p = st.back().second;
            st.pop_back();
            if (arr[u] >= 0) continue;
            arr[u] = t, rev[t] = u, par[t] = (p < 0) ? 0 : arr[p];
            lbl[t] = sdom[t] = dsu[t] = t;
            t++;
            for (int w : g[u])
            {
                if (arr[w] < 0) st.pb({w, u});
            }
        }
        rep(u, 0, n) if (arr[u] >= 0) for (int w : g[u]) rg[arr[w]].pb(arr[u]);
    }
    vi build(int root)
    {
        dfs(root);
        repb(i, t - 1, 0)
        {
            for (int w : rg[i]) sdom[i] = min(sdom[i], sdom[find(w)]);
            if (i) bucket[sdom[i]].pb(i);
            for (int w : bucket[i])
            {
                int v = find(w);
                dom[w] = (sdom[v] == sdom[w]) ? sdom[w] : v;
            }
            if (i > 1) dsu[i] = par[i];
        }
        rep(i, 1, t) if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
        vi idom(n, -1);
        rep(i, 0, t) idom[rev[i]] = rev[dom[i]];
        idom[root] = root;
        return idom;
    }
};
