// 2-sat. TwoSat ts(n) for variables 0..n-1. ts.either(a, va, b, vb) adds "(x_a == va) or (x_b == vb)"
// ts.solve() -> true if satisfiable, then ts.val[i] holds an assignment. iterative tarjan
struct TwoSat
{
    int n;
    vvi g;
    vi val;
    TwoSat(int n) : n(n), g(2 * n) {}
    int id(int x, bool v) { return 2 * x + (v ? 0 : 1); }
    void either(int a, bool va, int b, bool vb)
    {
        int A = id(a, va), B = id(b, vb);
        g[A ^ 1].pb(B), g[B ^ 1].pb(A);
    }
    void setTrue(int a, bool va) { either(a, va, a, va); }
    void implies(int a, bool va, int b, bool vb) { either(a, !va, b, vb); }
    bool solve()
    {
        int N = 2 * n, timer = 0, nc = 0;
        vi num(N, 0), low(N, 0), comp(N, -1), stk, it(N, 0);
        vector<char> on(N, 0);
        rep(s, 0, N)
        {
            if (num[s]) continue;
            vi call = {s};
            num[s] = low[s] = ++timer, stk.pb(s), on[s] = 1;
            while (!call.empty())
            {
                int v = call.back();
                if (it[v] < (int)g[v].size())
                {
                    int to = g[v][it[v]++];
                    if (!num[to]) num[to] = low[to] = ++timer, stk.pb(to), on[to] = 1, call.pb(to);
                    else if (on[to]) low[v] = min(low[v], num[to]);
                }
                else
                {
                    if (low[v] == num[v])
                    {
                        while (true)
                        {
                            int u = stk.back(); stk.pop_back();
                            on[u] = 0, comp[u] = nc;
                            if (u == v) break;
                        }
                        nc++;
                    }
                    call.pop_back();
                    if (!call.empty()) low[call.back()] = min(low[call.back()], low[v]);
                }
            }
        }
        val.assign(n, 0);
        rep(i, 0, n)
        {
            if (comp[2 * i] == comp[2 * i + 1]) return false;
            val[i] = comp[2 * i] < comp[2 * i + 1]; // tarjan numbers sinks first
        }
        return true;
    }
};
