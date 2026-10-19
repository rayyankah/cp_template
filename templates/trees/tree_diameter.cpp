// tree diameter by two bfs. returns {length (edges), {end a, end b}}; works for any node labels 0..n-1 / 1..n
pair<int, pi> diameter(const vvi &g, int start)
{
    auto bfs = [&](int s, vi &d)
    {
        d.assign(g.size(), -1);
        queue<int> q;
        d[s] = 0, q.push(s);
        int far = s;
        while (!q.empty())
        {
            int v = q.front(); q.pop();
            if (d[v] > d[far]) far = v;
            for (int u : g[v]) if (d[u] == -1) d[u] = d[v] + 1, q.push(u);
        }
        return far;
    };
    vi d1, d2;
    int a = bfs(start, d1), b = bfs(a, d2);
    return {d2[b], {a, b}};
}
// for every v: farthest distance = max(dist(a, v), dist(b, v))
