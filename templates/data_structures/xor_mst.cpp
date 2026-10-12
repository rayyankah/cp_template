// xor minimum spanning tree: sort indices by w into ord, edges.clear(), mst(0, n - 1, 29)
// edges gets the n - 1 tree edges (pairs of indices)
int w[200005];
vi ord;
int tr[200005 * 31][2], tid[200005 * 31], tc;
vpi edges;
void ins(int i)
{
    int v = 0;
    repb(b, 29, 0)
    {
        int c = w[i] >> b & 1;
        if (!tr[v][c]) tr[v][c] = ++tc, tr[tc][0] = tr[tc][1] = 0;
        v = tr[v][c];
    }
    tid[v] = i;
}
pi best(int i) // {min xor with w[i] in the trie, index}
{
    int v = 0, res = 0;
    repb(b, 29, 0)
    {
        int c = w[i] >> b & 1;
        if (tr[v][c]) v = tr[v][c];
        else v = tr[v][c ^ 1], res |= 1 << b;
    }
    return {res, tid[v]};
}
// xor minimum spanning tree of ord[l..r] (sorted by value), all equal above bit b
void mst(int l, int r, int b)
{
    if (l >= r || b < 0)
    {
        rep(i, l, r) edges.pb({ord[i], ord[i + 1]}); // equal values, any chain works
        return;
    }
    int m = l;
    while (m <= r && !(w[ord[m]] >> b & 1)) m++;
    mst(l, m - 1, b - 1), mst(m, r, b - 1);
    if (m <= l || m > r) return;
    tc = 0, tr[0][0] = tr[0][1] = 0;
    rep(i, l, m) ins(ord[i]);
    pi bst = {LLONG_MAX, 0};
    int who = -1;
    rep(i, m, r + 1)
    {
        pi got = best(ord[i]);
        if (got.first < bst.first) bst = got, who = ord[i];
    }
    edges.pb({who, bst.second});
}
