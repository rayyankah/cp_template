//edmonds karp (cses download speed)

void solve()
{
    int n, m;
    cin >> n >> m;
    vvi adj(n + 1);
    vvi capacity(n + 1, vi(n + 1, 0));
    rep(i, 0, m)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb(v);
        adj[v].pb(u);

        capacity[u][v] += w; // multiple edge
    }
    int flow = 0;
    while (true)
    {
        vi par(n + 1, -1);
        par[1] = -2;
        queue<pi> q;
        const int INF = 1e18;
        q.push({1, INF});
        bool tfound = false;
        while (!q.empty())
        {
            pi curr = q.front();

            q.pop();
            int u = curr.first;
            int flow_till_now = curr.second;
            for (auto &child : adj[u])
            {
                if (par[child] == -1 && capacity[u][child] > 0)
                {
                    int new_flow = min<ll>(flow_till_now, capacity[u][child]);
                    par[child] = u;
                    if (child == n)
                    {
                        tfound = true;
                        flow += new_flow;
                        int currv = child;
                        int s = 1;
                        while (currv != s)
                        {
                            int prev = par[currv];
                            capacity[prev][currv] -= new_flow;
                            capacity[currv][prev] += new_flow;
                            currv = prev;
                        }
                        break;
                    }
                    q.push({child, new_flow});
                }
                if (tfound)
                    break;
            }
        }
        if (!tfound)
            break;
    }
    cout << flow << nl;
}
