// sqrt decomposition: range "a[i] = min(a[i], x)" and range sum. ChminSum s(a); s.update(l, r, x); s.query(l, r)
// each block keeps its sorted values + prefix sums, and a lazy cap. O(sqrt(n) log n) per operation
struct ChminSum
{
    int n, B;
    vi a, cap;
    vvi srt, pre;
    ChminSum(const vi &v) : n(v.size()), a(v)
    {
        B = max(1LL, (int)sqrt(n));
        int k = (n + B - 1) / B;
        cap.assign(k, LLONG_MAX), srt.assign(k, vi()), pre.assign(k, vi());
        rep(b, 0, k) rebuild(b);
    }
    void push(int b) // apply the lazy cap to the real values
    {
        if (cap[b] == LLONG_MAX) return;
        rep(i, b * B, min(n, (b + 1) * B)) a[i] = min(a[i], cap[b]);
        cap[b] = LLONG_MAX;
    }
    void rebuild(int b)
    {
        srt[b].assign(a.begin() + b * B, a.begin() + min(n, (b + 1) * B));
        sort(all(srt[b]));
        pre[b].assign(srt[b].size() + 1, 0);
        rep(i, 0, (int)srt[b].size()) pre[b][i + 1] = pre[b][i] + srt[b][i];
    }
    int blockSum(int b) // sum of min(v, cap) over the block
    {
        int c = cap[b], k = lower_bound(all(srt[b]), c) - srt[b].begin();
        return pre[b][k] + (c == LLONG_MAX ? 0 : c * ((int)srt[b].size() - k));
    }
    void update(int l, int r, int x)
    {
        int bl = l / B, br = r / B;
        if (bl == br)
        {
            push(bl);
            rep(i, l, r + 1) a[i] = min(a[i], x);
            rebuild(bl);
            return;
        }
        push(bl); rep(i, l, (bl + 1) * B) a[i] = min(a[i], x); rebuild(bl);
        rep(b, bl + 1, br) cap[b] = min(cap[b], x);
        push(br); rep(i, br * B, r + 1) a[i] = min(a[i], x); rebuild(br);
    }
    int query(int l, int r)
    {
        int bl = l / B, br = r / B, s = 0;
        if (bl == br) { rep(i, l, r + 1) s += min(a[i], cap[bl]); return s; }
        rep(i, l, (bl + 1) * B) s += min(a[i], cap[bl]);
        rep(b, bl + 1, br) s += blockSum(b);
        rep(i, br * B, r + 1) s += min(a[i], cap[br]);
        return s;
    }
};
