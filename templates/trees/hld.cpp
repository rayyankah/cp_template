// heavy light decomposition. HLD h(g, root); positions h.pos[v] in [0, n) (subtree of v = [pos[v], pos[v] + sz[v] - 1])
// h.path(u, v, f): calls f(l, r) for O(log n) position ranges covering the path (vertex values)
// for edge values store the edge at its lower vertex and call h.path(u, v, f, true)
struct HLD
{
    int n;
    vi par, heavy, head, pos, dep, sz;
    HLD(const vvi &g, int root) : n(g.size()), par(n, -1), heavy(n, -1), head(n), pos(n), dep(n, 0), sz(n, 1)
    {
        vi order = {root};
        rep(i, 0, (int)order.size())
        {
            int v = order[i];
            for (int u : g[v]) if (u != par[v]) par[u] = v, dep[u] = dep[v] + 1, order.pb(u);
        }
        repb(i, (int)order.size() - 1, 1)
        {
            int v = order[i], p = par[v];
            sz[p] += sz[v];
            if (heavy[p] == -1 || sz[v] > sz[heavy[p]]) heavy[p] = v;
        }
        int t = 0; // dfs order, heavy child first, iterative
        vi st = {root};
        while (!st.empty())
        {
            int v = st.back(); st.pop_back();
            for (int u = v; u != -1; u = heavy[u])
            {
                head[u] = v, pos[u] = t++;
                for (int w : g[u]) if (w != par[u] && w != heavy[u]) st.pb(w);
            }
        }
    }
    template <class F> void path(int u, int v, F f, bool edges = false)
    {
        while (head[u] != head[v])
        {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            f(pos[head[u]], pos[u]);
            u = par[head[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        if (pos[u] + edges <= pos[v]) f(pos[u] + edges, pos[v]);
    }
    int lca(int u, int v)
    {
        while (head[u] != head[v])
        {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            u = par[head[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
};
