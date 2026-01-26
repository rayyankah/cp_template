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



//cses distinct routes
void solve()
{
    int n, m;
    cin >> n >> m;
    vvi adj(n + 1);
    vvi capacity(n + 1, vi(n + 1, 0));
    vvi original(n + 1, vi(n + 1, 0));
    rep(i, 0, m)
    {
        int u, v, w;
        cin >> u >> v;
        w = 1;
        adj[u].pb(v);
        adj[v].pb(u);
 
        capacity[u][v] += w;
        original[u][v] += w;
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
    vvi flow_mat(n + 1, vi(n + 1, 0));
    rep(u, 1, n + 1)
    {
        rep(v, 1, n + 1)
        {
            if (original[u][v] > 0)
                flow_mat[u][v] = original[u][v] - capacity[u][v];
        }
    }
 
    vvi paths;
    g_adj = adj;
    g_flow_mat = flow_mat;
 
    rep(i, 0, flow)
    {
        vi path;
        path.pb(1);
        if (!dfs(1, n, path))
            break;
        paths.pb(path);
    }
 
    cout << paths.size() << nl;
    for (auto &path : paths)
    {
        cout << (int)path.size() << nl;
        rep(i, 0, (int)path.size())
        {
            cout << path[i] << " ";
        }
        cout << nl;
    }
    return;
}


//b sec online

void solve()
{
    int m, h;
    cin >> m >> h;
    float r;
    cin >> r;
    vector<pair<float, float>> mice(m);
    rep(i, 0, m)
    {
        cin >> mice[i].first >> mice[i].second;
    }
    vector<pair<float, float>> holes(h);
    vi holecpa(h, 0);
    rep(i, 0, h)
    {
        cin >> holes[i].first >> holes[i].second;
        cin>>holecpa[i];
    }
    vvi adj(h + m + 2);
    vvi capacity(h + m + 2, vi(h + m + 2, 0));
    vvi original(h + m + 2, vi(h + m + 2, 0));

    rep(i, 0, m)
    {
        rep(j, 0, h)
        {
            float x1 = mice[i].first;
            float y1 = mice[i].second;
            float x2 = holes[j].first;
            float y2 = holes[j].second;
            float diffval = diff(x1, y1, x2, y2);
            if (diffval <= r)
            {
                adj[i].pb(j + m);
                adj[j + m].pb(i);
                capacity[i][j + m] = 1;
                original[i][j + m] = 1;
            }
        }
    }
    int flow = 0;
    int s = m + h;
    int t = m + h + 1;
    rep(i, 0, m)
    {
        adj[i].pb(s);
        adj[s].pb(i);
        capacity[s][i] = 1;
        original[s][i] = 1;
    }
    rep(i, 0, h)
    {
        int j = i + m;
        adj[j].pb(t);
        adj[t].pb(j);
        capacity[j][t] += holecpa[i];
        // original[j][t] += 1;
    }
    while (true)
    {
        vi par(m + h + 2, -1);
        par[s] = -2;
        queue<pi> q;
        const int INF = 1e18;
        q.push({s, INF});
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
                    if (child == t)
                    {
                        tfound = true;
                        flow += new_flow;
                        int currv = child;

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
