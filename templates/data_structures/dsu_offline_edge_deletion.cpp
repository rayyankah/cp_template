// offline edge deletions: answer "number of components after each deletion" by adding edges back in reverse
// input: n m q, m edges (1-indexed), q edge indices to delete (1-indexed). uses DSU from dsu.cpp
vi offlineDeletions(int n, const vpi &edges, const vi &del) // del = 0-based edge ids in deletion order
{
    int m = edges.size(), q = del.size();
    vector<char> removed(m, 0);
    for (int id : del) removed[id] = 1;
    DSU d(n + 1);
    int comps = n;
    rep(i, 0, m) if (!removed[i] && d.unite(edges[i].first, edges[i].second)) comps--;
    vi ans(q);
    repb(i, q - 1, 0)
    {
        ans[i] = comps; // components after the i-th deletion
        if (d.unite(edges[del[i]].first, edges[del[i]].second)) comps--;
    }
    return ans;
}
