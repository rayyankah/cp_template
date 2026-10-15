// kahn topological sort. adj[u] = nodes v with edge u -> v, nodes 1..n
// returns topo order; size < n means the graph has a cycle
// lexicographically smallest order: use priority_queue<int, vi, greater<int>> instead of queue
vi topoSort(int n, vvi &adj)
{
    vi indeg(n + 1, 0), order;
    rep(u, 1, n + 1) for (int v : adj[u]) indeg[v]++;
    queue<int> q;
    rep(u, 1, n + 1) if (indeg[u] == 0) q.push(u);
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        order.pb(u);
        for (int v : adj[u]) if (--indeg[v] == 0) q.push(v);
    }
    return order;
}
