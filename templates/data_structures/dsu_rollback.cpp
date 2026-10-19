// dsu with rollback (no path compression): unite, then undo the last union with rollback()
// use: offline dynamic connectivity (segment tree over time), divide and conquer
struct RollbackDSU
{
    vi p, sz;
    vector<pi> hist; // {attached root, old size of the other root}, {-1,-1} for a no-op
    int comps;
    RollbackDSU(int n) : p(n), sz(n, 1), comps(n) { iota(all(p), 0); }
    int find(int x) { while (x != p[x]) x = p[x]; return x; }
    bool unite(int a, int b)
    {
        a = find(a), b = find(b);
        if (a == b) { hist.pb({-1, -1}); return false; }
        if (sz[a] < sz[b]) swap(a, b);
        hist.pb({b, sz[a]});
        p[b] = a, sz[a] += sz[b], comps--;
        return true;
    }
    void rollback()
    {
        pi h = hist.back();
        hist.pop_back();
        if (h.first == -1) return;
        int b = h.first, a = p[b];
        sz[a] = h.second, p[b] = b, comps++;
    }
};
