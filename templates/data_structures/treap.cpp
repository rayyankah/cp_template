// implicit treap (array with split / merge): insert, erase, reverse, sum on ranges in O(log n)
// root = tmerge(root, tnew(x)) to append. reverse [l, r]: split into a | b | c, flip b, merge back
mt19937 trng(chrono::steady_clock::now().time_since_epoch().count());
struct TNode { int val, sum, pri, sz; bool rev; int l, r; };
vector<TNode> tp = {{0, 0, 0, 0, false, 0, 0}}; // node 0 = null
int tnew(int v) { tp.pb({v, v, (int)trng(), 1, false, 0, 0}); return tp.size() - 1; }
int tsz(int t) { return tp[t].sz; }
void tpull(int t) { if (t) tp[t].sz = 1 + tsz(tp[t].l) + tsz(tp[t].r), tp[t].sum = tp[t].val + tp[tp[t].l].sum + tp[tp[t].r].sum; }
void pushT(int t) { if (t && tp[t].rev) { swap(tp[t].l, tp[t].r); if (tp[t].l) tp[tp[t].l].rev ^= 1; if (tp[t].r) tp[tp[t].r].rev ^= 1; tp[t].rev = 0; } }
void tsplit(int t, int k, int &a, int &b) // first k elements go to a
{
    if (!t) { a = b = 0; return; }
    pushT(t);
    if (tsz(tp[t].l) < k) { tsplit(tp[t].r, k - tsz(tp[t].l) - 1, tp[t].r, b); a = t; }
    else { tsplit(tp[t].l, k, a, tp[t].l); b = t; }
    tpull(t);
}
int tmerge(int a, int b)
{
    if (!a || !b) return a ^ b;
    if (tp[a].pri > tp[b].pri) { pushT(a); tp[a].r = tmerge(tp[a].r, b); tpull(a); return a; }
    pushT(b); tp[b].l = tmerge(a, tp[b].l); tpull(b); return b;
}
void reverseRange(int &root, int l, int r) // 0-based inclusive
{
    int a, b, c;
    tsplit(root, l, a, b), tsplit(b, r - l + 1, b, c);
    tp[b].rev ^= 1;
    root = tmerge(tmerge(a, b), c);
}
int rangeSum(int &root, int l, int r)
{
    int a, b, c;
    tsplit(root, l, a, b), tsplit(b, r - l + 1, b, c);
    int s = tp[b].sum;
    root = tmerge(tmerge(a, b), c);
    return s;
}
void toArray(int t, vi &out) { if (!t) return; pushT(t); toArray(tp[t].l, out); out.pb(tp[t].val); toArray(tp[t].r, out); }
