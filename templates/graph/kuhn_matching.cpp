// kuhn bipartite matching. fill adj[left] with right vertices, matching(nleft, nright)
// after it, mt[right] = matched left vertex or -1
vvi adj;
vi mt, used;
int stamp;
bool kuhn(int v)
{
    if (used[v] == stamp) return false;
    used[v] = stamp;
    for (int u : adj[v])
        if (mt[u] < 0 || kuhn(mt[u]))
        {
            mt[u] = v;
            return true;
        }
    return false;
}
// returns size of max matching, mt[right] = left
int matching(int n, int m)
{
    mt.assign(m, -1), used.assign(n, 0);
    int res = 0;
    rep(v, 0, n)
    {
        stamp++;
        if (kuhn(v)) res++;
    }
    return res;
}
