// li chao tree: add lines y = kx + b, query the minimum at integer x in [lo, hi]. O(log) each
// for maximum: insert (-k, -b) and negate the answer
struct LiChao
{
    struct Line { int k, b; int eval(int x) const { return k * x + b; } };
    int lo, hi;
    vector<Line> t;
    vi L, R;
    LiChao(int lo, int hi) : lo(lo), hi(hi) { newNode(); }
    int newNode() { t.pb({0, LLONG_MAX}), L.pb(-1), R.pb(-1); return t.size() - 1; }
    void add(Line ln, int v = 0, int l = LLONG_MIN, int r = LLONG_MIN)
    {
        if (l == LLONG_MIN) l = lo, r = hi;
        while (true)
        {
            int m = l + (r - l) / 2;
            bool lef = ln.eval(l) < t[v].eval(l), mid = ln.eval(m) < t[v].eval(m);
            if (t[v].b == LLONG_MAX) { t[v] = ln; return; }
            if (mid) swap(t[v], ln);
            if (l == r) return;
            if (lef != mid)
            {
                if (L[v] == -1) { int u = newNode(); L[v] = u; }
                v = L[v], r = m;
            }
            else
            {
                if (R[v] == -1) { int u = newNode(); R[v] = u; }
                v = R[v], l = m + 1;
            }
        }
    }
    int query(int x)
    {
        int v = 0, l = lo, r = hi, res = LLONG_MAX;
        while (v != -1)
        {
            if (t[v].b != LLONG_MAX) res = min(res, t[v].eval(x));
            int m = l + (r - l) / 2;
            if (x <= m) v = L[v], r = m; else v = R[v], l = m + 1;
        }
        return res;
    }
};
