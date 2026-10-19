// dsu with parity: unite(a, b, d) forces side(a) xor side(b) = d, returns false on contradiction
// ParityDSU d(n); d.find(v) = {root, side of v relative to root}. iterative, union by size
struct ParityDSU
{
    vi p, sz, rel; // rel = side of v relative to p[v] (0 same, 1 different)
    ParityDSU(int n) : p(n), sz(n, 1), rel(n, 0) { iota(all(p), 0); }
    pi find(int v)
    {
        int r = v, x = 0;
        while (p[r] != r) x ^= rel[r], r = p[r];
        int cur = x; // compress: every node on the path points to r
        while (p[v] != v)
        {
            int nxt = p[v], c = rel[v];
            p[v] = r, rel[v] = cur;
            cur ^= c, v = nxt;
        }
        return {r, x};
    }
    bool unite(int a, int b, int d)
    {
        pi A = find(a), B = find(b);
        if (A.first == B.first) return (A.second ^ B.second) == d;
        if (sz[A.first] < sz[B.first]) swap(A, B);
        p[B.first] = A.first, rel[B.first] = A.second ^ B.second ^ d, sz[A.first] += sz[B.first];
        return true;
    }
};
