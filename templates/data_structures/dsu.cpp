// dsu with union by size + path compression. DSU d(n); d.find(x); d.unite(a, b); d.size(x); d.comps
struct DSU
{
    vi p, sz;
    int comps;
    DSU(int n) : p(n), sz(n, 1), comps(n) { iota(all(p), 0); }
    int find(int x)
    {
        while (x != p[x]) x = p[x] = p[p[x]];
        return x;
    }
    bool unite(int a, int b) // false if already together
    {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a, sz[a] += sz[b], comps--;
        return true;
    }
    bool same(int a, int b) { return find(a) == find(b); }
    int size(int x) { return sz[find(x)]; }
};
