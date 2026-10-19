// kruskal minimum spanning tree. edges {w, u, v}. returns {total weight, chosen edges}; needs DSU (dsu.cpp)
// total < 0 never happens; if result.second.size() < n - 1 the graph is disconnected
pair<int, vector<array<int, 3>>> kruskal(int n, vector<array<int, 3>> e)
{
    sort(all(e));
    DSU d(n);
    int total = 0;
    vector<array<int, 3>> used;
    for (auto &x : e) if (d.unite(x[1], x[2])) total += x[0], used.pb(x);
    return {total, used};
}
