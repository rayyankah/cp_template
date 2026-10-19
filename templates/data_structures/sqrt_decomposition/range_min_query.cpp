// sqrt decomposition: point update, range min. SqrtMin s(a); s.update(i, x); s.query(l, r) inclusive
struct SqrtMin
{
    int n, B;
    vi a, blk;
    SqrtMin(const vi &v) : n(v.size()), a(v)
    {
        B = max(1LL, (int)sqrt(n));
        blk.assign(n / B + 1, LLONG_MAX);
        rep(i, 0, n) blk[i / B] = min(blk[i / B], a[i]);
    }
    void update(int i, int x)
    {
        a[i] = x;
        int b = i / B;
        blk[b] = LLONG_MAX;
        rep(j, b * B, min(n, (b + 1) * B)) blk[b] = min(blk[b], a[j]);
    }
    int query(int l, int r)
    {
        int res = LLONG_MAX;
        while (l <= r && l % B) res = min(res, a[l++]);
        while (l + B - 1 <= r) res = min(res, blk[l / B]), l += B;
        while (l <= r) res = min(res, a[l++]);
        return res;
    }
};
