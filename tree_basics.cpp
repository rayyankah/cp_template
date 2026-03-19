// sum of distances among all pair of nodes..
    vi sz(n + 1, 0);
    int sumofdist = 0;
    function<void(int, int)> dfs = [&](int u, int parent)
    {
        sz[u] = 1;
        for (int v : adj[u])
        {
            if (v != parent)
            {
                dfs(v, u);
                sz[u] += sz[v];
                sumofdist += (sz[v] * (n - sz[v]));
            }
        }
    };

    dfs(1, 0);
