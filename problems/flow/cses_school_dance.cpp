//cses school dance
void solve()
{
    int n, mm, m;
    cin >> n >> mm >> m;
    vvi adj(n + mm + 2);
    vvi capacity(n + mm + 2, vi(n + mm + 2, 0));
    vpi edges;
    map<pi, int> init_cap;
    rep(i, 0, m)
    {
        int u, v, w;
        cin >> u >> v;
        v += n;
        w = 1;
        adj[u].pb(v);
        adj[v].pb(u);
 
        capacity[u][v] += w;
        edges.pb({u, v});
        init_cap[{u, v}] = w;
    }
    rep(i, 1, n + 1)
    {
        adj[0].pb(i);
        adj[i].pb(0);
        capacity[0][i] = 1;
    }
    rep(i, n + 1, n + mm + 1)
    {
        adj[i].pb(n + mm + 1);
        adj[n + mm + 1].pb(i);
        capacity[i][n + mm + 1] = 1;
        capacity[n + mm + 1][i] = 0;
    }
    int flow = 0;
    while (true)
    {
        vi par(n + mm + 2, -1);
        par[0] = -2;
        queue<pi> q;
        const int INF = 1e18;
        q.push({0, INF});
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
                    if (child == n + mm + 1)
                    {
                        tfound = true;
                        flow += new_flow;
                        int currv = child;
                        int s = 0;
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
    vpi ans;
    rep(i, 0, m)
    {
        int u = edges[i].first;
        int v = edges[i].second;
        if (capacity[v][u] == 1)
        {
            ans.pb({u, v - n});
        }
    }
    rep(i, 0, flow)
    {
        cout << ans[i].first << " " << ans[i].second << nl;
    }
}
