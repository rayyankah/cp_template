struct scc
{
    int n, timer, nc;
    vvi g, comps;
    vi comp, num, low, stk;
    vector<bool> onstk;

    scc(int n) : n(n), timer(0), nc(0), g(n), comp(n, -1), num(n, 0), low(n, 0), onstk(n, false) {}

    void add_edge(int u, int v) { g[u].pb(v); }

    void run(int root)
    {
        vpi call;
        num[root] = low[root] = ++timer;
        stk.pb(root);
        onstk[root] = true;
        call.pb({root, 0});
        while (!call.empty())
        {
            int v = call.back().first;
            int i = call.back().second;
            if (i < (int)g[v].size())
            {
                call.back().second = i + 1;
                int to = g[v][i];
                if (!num[to])
                {
                    num[to] = low[to] = ++timer;
                    stk.pb(to);
                    onstk[to] = true;
                    call.pb({to, 0});
                }
                else if (onstk[to]) low[v] = min(low[v], num[to]);
            }
            else
            {
                if (low[v] == num[v])
                {
                    vi cur;
                    while (true)
                    {
                        int u = stk.back();
                        stk.pop_back();
                        onstk[u] = false;
                        comp[u] = nc;
                        cur.pb(u);
                        if (u == v) break;
                    }
                    comps.pb(cur);
                    nc++;
                }
                call.pop_back();
                if (!call.empty()) low[call.back().first] = min(low[call.back().first], low[v]);
            }
        }
    }

    void build() { rep(i, 0, n) if (!num[i]) run(i); }
};  




scc sc(n + 1);
sc.add_edge(a, b);
sc.build();
// sc.comp[v] = component id of v
// sc.comps   = list of components, sinks first
// sc.g       = the graph (reuse it, don't build a second one)
