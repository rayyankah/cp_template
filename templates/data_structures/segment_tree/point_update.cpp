// iterative segment tree: point set, range query (any associative op). SegTree st(n); st.set(i, v); st.query(l, r) inclusive
struct SegTree
{
    int n;
    vi t;
    const int ID = 0;                                 // identity: 0 for sum, LLONG_MIN for max, LLONG_MAX for min
    static int op(int a, int b) { return a + b; }     // change to max / min / __gcd
    SegTree(int n) : n(n), t(2 * n, 0) {}
    SegTree(const vi &a) : n(a.size()), t(2 * a.size())
    {
        rep(i, 0, n) t[n + i] = a[i];
        repb(i, n - 1, 1) t[i] = op(t[2 * i], t[2 * i + 1]);
    }
    void set(int i, int v)
    {
        for (t[i += n] = v; i > 1; i >>= 1) t[i >> 1] = op(t[i & ~1LL], t[i | 1]);
    }
    int query(int l, int r) // result of op over [l, r]; op must be commutative here
    {
        int res = ID;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1) res = op(res, t[l++]);
            if (r & 1) res = op(res, t[--r]);
        }
        return res;
    }
};
