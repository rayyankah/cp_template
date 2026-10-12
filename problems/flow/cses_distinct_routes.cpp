//cses distinct routes
vvi g_adj;
vvi g_flow_mat;
 
bool dfs(int u, int t, vi &path)
{
    if (u == t)
        return true;
    for (int v : g_adj[u])
    {
        if (g_flow_mat[u][v] > 0)
        {
            g_flow_mat[u][v]--;
            path.pb(v);
            if (dfs(v, t, path))
                return true;
            path.pop_back();
            g_flow_mat[u][v]++;
        }
    }
    return false;
}

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
