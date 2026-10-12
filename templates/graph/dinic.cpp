// dinic max flow. dinic d(n); d.add(u, v, cap, reverse_cap); d.flow(s, t)
// min cut = max flow
struct edge
{
    int to, cap;
};
struct dinic
{
    vector<edge> e;
    vvi g;
    vi lvl, it;
    dinic(int n) : g(n), lvl(n), it(n) {}
    void add(int u, int v, int c, int rc = 0)
    {
        g[u].pb(e.size()), e.pb({v, c});
        g[v].pb(e.size()), e.pb({u, rc});
    }
    bool bfs(int s, int t)
    {
        fill(all(lvl), -1);
        lvl[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int id : g[u])
                if (e[id].cap > 0 && lvl[e[id].to] < 0) lvl[e[id].to] = lvl[u] + 1, q.push(e[id].to);
        }
        return lvl[t] >= 0;
    }
    int dfs(int u, int t, int f)
    {
        if (u == t) return f;
        for (int &i = it[u]; i < (int)g[u].size(); i++)
        {
            int id = g[u][i], v = e[id].to;
            if (e[id].cap > 0 && lvl[v] == lvl[u] + 1)
            {
                int d = dfs(v, t, min(f, e[id].cap));
                if (d > 0)
                {
                    e[id].cap -= d, e[id ^ 1].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    int flow(int s, int t)
    {
        int res = 0;
        while (bfs(s, t))
        {
            fill(all(it), 0);
            while (int f = dfs(s, t, LLONG_MAX)) res += f;
        }
        return res;
    }
};
