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




//cses police chase (min cut)
void solve()
{
    int n, m;
    cin >> n >> m;
    vpi edges;
    vvi adj(n + 1);
    vvi capacity(n + 1, vi(n + 1, 0));
    map<pi, int> init_cap;
    rep(i, 0, m)
    {
        int u, v, w;
        cin >> u >> v;
        w = 1;
        adj[u].pb(v);
        adj[v].pb(u);
        edges.pb({u, v});
        edges.pb({v, u});
        init_cap[{u, v}] = w;
        init_cap[{v, u}] = w;
        capacity[u][v] += w;
        capacity[v][u] += w;
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
    vi id(n + 1, 2);
    id[1] = 1;
    // nodes reachable from source ->id 1
    vi vis(n + 1, 0);
    function<void(int, int)> dfs = [&](int u, int par)
    {
        vis[u] = 1;
        for (auto &child : adj[u])
        {
            debug(u);
            debug(child);
            if (capacity[u][child] > 0 && !vis[child])
            {
                id[child] = 1;
                dfs(child, u);
            }
        }
    };
    debug(id);
    dfs(1, -1);
    int min_cut = 0;
    vpi ans;
    for (auto &edge : edges)
    {
        int u = edge.first;
        int v = edge.second;
        if (id[u] == 1 && id[v] == 2)
        {
            min_cut += init_cap[{u, v}];
            ans.pb({u, v});
        }
    }
    cout << (int)ans.size() << nl;
    rep(i, 0, (int)ans.size())
    {
        cout << ans[i].first << " " << ans[i].second << nl;
    }
}



