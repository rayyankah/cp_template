// 0-1 bfs: shortest paths when every weight is 0 or 1, O(n + m). g[u] = {v, w}, w in {0, 1}
vi bfs01(const vector<vpi> &g, int s)
{
    vi d(g.size(), LLONG_MAX);
    deque<int> dq;
    d[s] = 0, dq.pb(s);
    while (!dq.empty())
    {
        int u = dq.front();
        dq.pop_front();
        for (auto &e : g[u]) { int v = e.first, w = e.second; if (d[u] + w < d[v])
        {
            d[v] = d[u] + w;
            if (w == 0) dq.push_front(v); else dq.pb(v);
        } }
    }
    return d;
}
// multi-source bfs on a grid: push every source with distance 0 first. '#' = wall
vvi gridBfs(const vector<string> &g, const vpi &src)
{
    int R = g.size(), C = g[0].size();
    vvi d(R, vi(C, -1));
    queue<pi> q;
    for (auto &p : src) d[p.first][p.second] = 0, q.push(p);
    int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    while (!q.empty())
    {
        int r = q.front().first, c = q.front().second;
        q.pop();
        rep(k, 0, 4)
        {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nc < 0 || nr >= R || nc >= C || g[nr][nc] == '#' || d[nr][nc] != -1) continue;
            d[nr][nc] = d[r][c] + 1, q.push({nr, nc});
        }
    }
    return d;
}
// knight moves: dr = {1,2,2,1,-1,-2,-2,-1}, dc = {2,1,-1,-2,-2,-1,1,2}
