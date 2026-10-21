// hashing with point updates: change a character, compare / test palindrome on any range in O(log n)
// DynHash h(s); h.set(i, c); h.get(l, r) = hash of s[l..r]
// segment tree: each node keeps the hash of its segment, merge = left * B^(length of right) + right
struct DynHash
{
    static const int M1 = 1000000007, M2 = 1000000009, B = 131;
    struct node { int h1, h2, len; };
    int n;
    vi pw1, pw2;
    vector<node> seg;
    node identity() { return {0, 0, 0}; }
    node makeLeaf(int c) { return {c % M1, c % M2, 1}; }
    node merge(node L, node R)
    {
        return {(L.h1 * pw1[R.len] + R.h1) % M1, (L.h2 * pw2[R.len] + R.h2) % M2, L.len + R.len};
    }
    void build(int idx, int l, int r, const string &s)
    {
        if (l == r) { seg[idx] = makeLeaf((unsigned char)s[l]); return; }
        int mid = l + (r - l) / 2;
        build(2 * idx + 1, l, mid, s);
        build(2 * idx + 2, mid + 1, r, s);
        seg[idx] = merge(seg[2 * idx + 1], seg[2 * idx + 2]);
    }
    void pointUpdate(int idx, int l, int r, int pos, int c)
    {
        if (l == r) { seg[idx] = makeLeaf(c); return; }
        int mid = l + (r - l) / 2;
        if (pos <= mid) pointUpdate(2 * idx + 1, l, mid, pos, c);
        else pointUpdate(2 * idx + 2, mid + 1, r, pos, c);
        seg[idx] = merge(seg[2 * idx + 1], seg[2 * idx + 2]);
    }
    node query(int idx, int l, int r, int ql, int qr)
    {
        if (l > qr || r < ql) return identity();
        if (ql <= l && r <= qr) return seg[idx];
        int mid = l + (r - l) / 2;
        return merge(query(2 * idx + 1, l, mid, ql, qr), query(2 * idx + 2, mid + 1, r, ql, qr));
    }
    DynHash(const string &s) : n(s.size()), pw1(n + 1, 1), pw2(n + 1, 1), seg(4 * max(1LL, (int)s.size()))
    {
        rep(i, 1, n + 1) pw1[i] = pw1[i - 1] * B % M1, pw2[i] = pw2[i - 1] * B % M2;
        if (n) build(0, 0, n - 1, s);
    }
    void set(int i, int c) { pointUpdate(0, 0, n - 1, i, c); } // s[i] = c
    pi get(int l, int r) // hash of s[l..r]
    {
        if (l > r) return {0, 0};
        node x = query(0, 0, n - 1, l, r);
        return {x.h1, x.h2};
    }
};
// palindrome check on s[l..r] with updates: keep DynHash f(s) and g(reversed s);
// s[l..r] is a palindrome  <=>  f.get(l, r) == g.get(n - 1 - r, n - 1 - l)
