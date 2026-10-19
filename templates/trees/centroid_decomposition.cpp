// centroid decomposition. Centroid cd(g); cd.cpar[v] = parent in the centroid tree (-1 for the root)
// cd.anc[v] = list of {centroid ancestor, distance} (including v itself at distance 0), O(n log n) memory
// typical use: nearest marked vertex -> best[c] = min dist; mark v: for (c, d) in anc[v] best[c] = min(best[c], d)
struct Centroid
{
    int n;
    const vvi &g;
    vi sz, cpar;
    vector<char> removed;
    vector<vpi> anc;
    Centroid(const vvi &g) : n(g.size()), g(g), sz(n), cpar(n, -1), removed(n, 0), anc(n) { build(0, -1); }
    void calc(int s) // subtree sizes in the current piece, iterative
    {
        vi order = {s}, pr = {-1};
        for (int i = 0; i < (int)order.size(); i++)
        {
            int v = order[i];
            for (int u : g[v]) if (u != pr[i] && !removed[u]) order.pb(u), pr.pb(v);
        }
        repb(i, (int)order.size() - 1, 0)
        {
            int v = order[i];
            sz[v] = 1;
            for (int u : g[v]) if (u != pr[i] && !removed[u]) sz[v] += sz[u];
        }
    }
    int centroid(int s)
    {
        calc(s);
        int total = sz[s], v = s, p = -1;
        while (true)
        {
            int nxt = -1;
            for (int u : g[v]) if (u != p && !removed[u] && sz[u] < sz[v] && sz[u] * 2 > total) nxt = u;
            if (nxt == -1) return v;
            p = v, v = nxt;
        }
    }
    void build(int s, int p)
    {
        int c = centroid(s);
        cpar[c] = p;
        vi order = {c}, dist = {0}, pr = {-1}; // distances from c inside the piece
        for (int i = 0; i < (int)order.size(); i++)
        {
            int v = order[i];
            anc[v].pb({c, dist[i]});
            for (int u : g[v]) if (u != pr[i] && !removed[u]) order.pb(u), dist.pb(dist[i] + 1), pr.pb(v);
        }
        removed[c] = 1;
        for (int u : g[c]) if (!removed[u]) build(u, c);
    }
};
