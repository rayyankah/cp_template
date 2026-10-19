// sparse table, O(1) idempotent range query (min / max / gcd). SparseTable st(a); st.query(l, r) inclusive
struct SparseTable
{
    vvi t;
    static int op(int a, int b) { return min(a, b); } // change to max / __gcd
    SparseTable(const vi &a)
    {
        int n = a.size(), k = 64 - __builtin_clzll(max(n, 1LL));
        t.assign(k, vi(n));
        t[0] = a;
        rep(j, 1, k) rep(i, 0, n - (1LL << j) + 1) t[j][i] = op(t[j - 1][i], t[j - 1][i + (1LL << (j - 1))]);
    }
    int query(int l, int r)
    {
        int j = 63 - __builtin_clzll(r - l + 1);
        return op(t[j][l], t[j][r - (1LL << j) + 1]);
    }
};
