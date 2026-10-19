// min cost max flow (successive shortest paths with spfa; costs may be negative but no negative cycles)
// MCMF f(n); f.add(u, v, cap, cost); auto r = f.flow(s, t, maxFlow = INF) -> {flow, cost}
struct MCMF
{
    struct E { int to, cap, cost; };
    int n;
    vector<E> e;
    vvi g;
    MCMF(int n) : n(n), g(n) {}
    void add(int u, int v, int cap, int cost)
    {
        g[u].pb(e.size()), e.pb({v, cap, cost});
        g[v].pb(e.size()), e.pb({u, 0, -cost});
    }
    pi flow(int s, int t, int maxFlow = LLONG_MAX)
    {
        int fl = 0, cost = 0;
        while (fl < maxFlow)
        {
            vi d(n, LLONG_MAX), pe(n, -1);
            vector<char> inq(n, 0);
            deque<int> q;
            d[s] = 0, q.pb(s), inq[s] = 1;
            while (!q.empty())
            {
                int v = q.front(); q.pop_front();
                inq[v] = 0;
                for (int id : g[v])
                    if (e[id].cap > 0 && d[v] + e[id].cost < d[e[id].to])
                    {
                        d[e[id].to] = d[v] + e[id].cost, pe[e[id].to] = id;
                        if (!inq[e[id].to]) inq[e[id].to] = 1, q.pb(e[id].to);
                    }
            }
            if (d[t] == LLONG_MAX) break;
            int push = maxFlow - fl;
            for (int v = t; v != s; v = e[pe[v] ^ 1].to) push = min(push, e[pe[v]].cap);
            for (int v = t; v != s; v = e[pe[v] ^ 1].to) e[pe[v]].cap -= push, e[pe[v] ^ 1].cap += push;
            fl += push, cost += push * d[t];
        }
        return {fl, cost};
    }
};
