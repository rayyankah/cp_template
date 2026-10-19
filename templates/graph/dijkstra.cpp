// dijkstra, O((n + m) log n). g[u] = {v, w}, w >= 0. returns dist (LLONG_MAX = unreachable), par for the path
vi dijkstra(const vector<vpi> &g, int s, vi *par = nullptr)
{
    int n = g.size();
    vi d(n, LLONG_MAX);
    if (par) par->assign(n, -1);
    priority_queue<pi, vpi, greater<pi>> pq;
    d[s] = 0, pq.push({0, s});
    while (!pq.empty())
    {
        int dv = pq.top().first, v = pq.top().second;
        pq.pop();
        if (dv != d[v]) continue; // outdated entry
        for (auto &e : g[v])
            if (dv + e.second < d[e.first])
            {
                d[e.first] = dv + e.second, pq.push({d[e.first], e.first});
                if (par) (*par)[e.first] = v;
            }
    }
    return d;
}
// 0-1 bfs: weights only 0 or 1, O(n + m)
vi bfs01(const vector<vpi> &g, int s)
{
    vi d(g.size(), LLONG_MAX);
    deque<int> dq;
    d[s] = 0, dq.pb(s);
    while (!dq.empty())
    {
        int v = dq.front(); dq.pop_front();
        for (auto &e : g[v])
            if (d[v] + e.second < d[e.first])
            {
                d[e.first] = d[v] + e.second;
                if (e.second == 0) dq.push_front(e.first); else dq.pb(e.first);
            }
    }
    return d;
}
