//GRAPH COLORING
void solve()
{
    int n, m;
    cin >> n >> m;
    vi adj[n + 1];
    rep(i, 1, m + 1)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vi colors(n + 1, 0);
    function<void(int)> dfs = [&](int node)
    {
        // this node is visited and assigned a color
        for (int child : adj[node])
        {
            if (colors[child] == 0)
            {
                // unvisited child,assigning a color
                colors[child] = colors[node] == 1 ? 2 : 1;
                // dfs chalabe ke???
                dfs(child);
            }

            // visited and ancestor
            else
            {
                if (colors[child] + colors[node] != 3)
                {
                    cout << "IMPOSSIBLE" << nl;
                    exit(0);
                }
            }
        }
    };
    rep(i, 1, n + 1)
    {
        if (colors[i] == 0)
        {
            // unvisited so is not assigned color
            colors[i] = 1;
            dfs(i);
        }
    }
    rep(i, 1, n + 1)
    {
        cout << colors[i] << " ";
    }
    cout << nl;
}
