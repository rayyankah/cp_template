// lazy segment tree: range add, range sum. LazySum st(n) (or LazySum st(a)); st.add(l, r, v); st.sum(l, r), 0-based inclusive
struct LazySum
{
    int n;
    vi t, lz;
    LazySum(int n) : n(n), t(4 * n, 0), lz(4 * n, 0) {}
    LazySum(const vi &a) : LazySum(a.size()) { build(1, 0, n - 1, a); }
    void build(int x, int l, int r, const vi &a)
    {
        if (l == r) { t[x] = a[l]; return; }
        int m = (l + r) / 2;
        build(2 * x, l, m, a), build(2 * x + 1, m + 1, r, a);
        t[x] = t[2 * x] + t[2 * x + 1];
    }
    void apply(int x, int l, int r, int v) { t[x] += v * (r - l + 1), lz[x] += v; }
    void push(int x, int l, int r)
    {
        if (!lz[x]) return;
        int m = (l + r) / 2;
        apply(2 * x, l, m, lz[x]), apply(2 * x + 1, m + 1, r, lz[x]);
        lz[x] = 0;
    }
    void add(int ql, int qr, int v, int x = 1, int l = 0, int r = -1)
    {
        if (r == -1) r = n - 1;
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) { apply(x, l, r, v); return; }
        push(x, l, r);
        int m = (l + r) / 2;
        add(ql, qr, v, 2 * x, l, m), add(ql, qr, v, 2 * x + 1, m + 1, r);
        t[x] = t[2 * x] + t[2 * x + 1];
    }
    int sum(int ql, int qr, int x = 1, int l = 0, int r = -1)
    {
        if (r == -1) r = n - 1;
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return t[x];
        push(x, l, r);
        int m = (l + r) / 2;
        return sum(ql, qr, 2 * x, l, m) + sum(ql, qr, 2 * x + 1, m + 1, r);
    }
};
