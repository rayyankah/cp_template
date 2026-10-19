// fenwick tree (BIT), 0-based outside. BIT b(n); b.add(i, v); b.sum(r) = a[0..r]; b.sum(l, r)
// b.lowerBound(k): smallest i with a[0..i] >= k (all values non-negative), n if none
struct BIT
{
    int n;
    vi t;
    BIT(int n) : n(n), t(n + 1, 0) {}
    void add(int i, int v) { for (i++; i <= n; i += i & -i) t[i] += v; }
    int sum(int r) { int s = 0; for (r++; r > 0; r -= r & -r) s += t[r]; return s; }
    int sum(int l, int r) { return l > r ? 0 : sum(r) - sum(l - 1); }
    int lowerBound(int k)
    {
        int pos = 0, LOG = 1;
        while ((LOG << 1) <= n) LOG <<= 1;
        for (int step = LOG; step; step >>= 1)
            if (pos + step <= n && t[pos + step] < k) pos += step, k -= t[pos];
        return pos; // 0-based index
    }
};
// range add + range sum with two BITs. RangeBIT b(n); b.add(l, r, v); b.sum(l, r)
struct RangeBIT
{
    BIT b1, b2;
    RangeBIT(int n) : b1(n + 1), b2(n + 1) {}
    void add(int l, int r, int v) { b1.add(l, v), b1.add(r + 1, -v), b2.add(l, v * l), b2.add(r + 1, -v * (r + 1)); }
    int pref(int r) { return b1.sum(r) * (r + 1) - b2.sum(r); }
    int sum(int l, int r) { return pref(r) - (l ? pref(l - 1) : 0); }
};
// 2d fenwick, point add, rectangle sum (0-based, inclusive)
struct BIT2D
{
    int n, m;
    vvi t;
    BIT2D(int n, int m) : n(n), m(m), t(n + 1, vi(m + 1, 0)) {}
    void add(int x, int y, int v) { for (int i = x + 1; i <= n; i += i & -i) for (int j = y + 1; j <= m; j += j & -j) t[i][j] += v; }
    int sum(int x, int y) { int s = 0; for (int i = x + 1; i > 0; i -= i & -i) for (int j = y + 1; j > 0; j -= j & -j) s += t[i][j]; return s; }
    int sum(int x1, int y1, int x2, int y2) { return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1); }
};
// inversion count: compress values, then for each element count bigger ones already seen
