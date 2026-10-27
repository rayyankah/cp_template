// segment tree with a CUSTOM node and merge (point update, range query). the merge does not need to be
// commutative. change Node, ID(), leaf(), merge(). example below: bracket matching (CF 380C style):
// longest correct bracket subsequence in s[l..r] = 2 * (matched pairs)
struct Node { int match, open, close; }; // matched pairs, unmatched '(' , unmatched ')'
Node ID() { return {0, 0, 0}; }
Node leaf(char c) { return c == '(' ? Node{0, 1, 0} : Node{0, 0, 1}; }
Node merge(const Node &a, const Node &b)
{
    int t = min(a.open, b.close); // left's open brackets close with right's close brackets
    return {a.match + b.match + t, a.open + b.open - t, a.close + b.close - t};
}
struct SegCustom
{
    int n;
    vector<Node> t;
    SegCustom(const string &s) : n(s.size()), t(4 * s.size()) { build(1, 0, n - 1, s); }
    void build(int x, int l, int r, const string &s)
    {
        if (l == r) { t[x] = leaf(s[l]); return; }
        int m = (l + r) / 2;
        build(2 * x, l, m, s), build(2 * x + 1, m + 1, r, s);
        t[x] = merge(t[2 * x], t[2 * x + 1]);
    }
    void update(int i, char c, int x = 1, int l = 0, int r = -1)
    {
        if (r < 0) r = n - 1;
        if (l == r) { t[x] = leaf(c); return; }
        int m = (l + r) / 2;
        if (i <= m) update(i, c, 2 * x, l, m); else update(i, c, 2 * x + 1, m + 1, r);
        t[x] = merge(t[2 * x], t[2 * x + 1]);
    }
    Node query(int ql, int qr, int x = 1, int l = 0, int r = -1) // left-to-right order is kept
    {
        if (r < 0) r = n - 1;
        if (qr < l || r < ql) return ID();
        if (ql <= l && r <= qr) return t[x];
        int m = (l + r) / 2;
        return merge(query(ql, qr, 2 * x, l, m), query(ql, qr, 2 * x + 1, m + 1, r));
    }
};
// other useful nodes: max subarray sum {sum, best prefix, best suffix, best}; count + min; hash of a range
