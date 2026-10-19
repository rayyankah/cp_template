// bellman ford, O(nm). edges {u, v, w}. returns dist from s (LLONG_MAX = unreachable);
// negInf[v] = 1 if v can be made arbitrarily small (reachable from a negative cycle reachable from s)
vi bellmanFord(int n, const vector<array<int, 3>> &e, int s, vi &negInf)
{
    vi d(n, LLONG_MAX);
    negInf.assign(n, 0);
    d[s] = 0;
    rep(it, 0, n - 1) for (auto &x : e)
        if (d[x[0]] != LLONG_MAX && d[x[0]] + x[2] < d[x[1]]) d[x[1]] = d[x[0]] + x[2];
    rep(it, 0, n) for (auto &x : e) // spread "minus infinity"
        if (d[x[0]] != LLONG_MAX && (negInf[x[0]] || d[x[0]] + x[2] < d[x[1]])) negInf[x[1]] = 1;
    return d;
}
// any negative cycle in the whole graph (as a vertex list), empty if none
vi findNegCycle(int n, const vector<array<int, 3>> &e)
{
    vi d(n, 0), p(n, -1);
    int x = -1;
    rep(it, 0, n)
    {
        x = -1;
        for (auto &y : e) if (d[y[0]] + y[2] < d[y[1]]) d[y[1]] = d[y[0]] + y[2], p[y[1]] = y[0], x = y[1];
    }
    if (x == -1) return {};
    rep(i, 0, n) x = p[x];
    vi cyc;
    for (int v = x;; v = p[v]) { cyc.pb(v); if (v == x && cyc.size() > 1) break; }
    reverse(all(cyc));
    return cyc; // first == last
}
