//a sec online
//================ Code starts here ================
void solve()
{
    int n, m;
    cin >> n >> m;

    vector<pair<double, pair<int,int>>> edges(m);
    vector<ll> real_w(m);

    rep(i, 0, m)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        edges[i] = {log((double)w), {u, v}};
        real_w[i] = w;
    }

    // ---------- First MST (minimum product) ----------
    rep(i, 0, n) make(i);

    vector<int> mst_idx;
    double best_log = 0;

    vector<int> ord(m);
    iota(all(ord), 0);
    sort(all(ord), [&](int a, int b) {
        return edges[a].first < edges[b].first;
    });

    for (int id : ord)
    {
        int u = edges[id].second.first;
        int v = edges[id].second.second;
        if (find(u) != find(v))
        {
            Union(u, v);
            mst_idx.pb(id);
            best_log += edges[id].first;
        }
    }

    if ((int)mst_idx.size() != n - 1)
    {
        cout << -1 << nl;
        return;
    }

    // ---------- Second MST ----------
    double second_log = 1e100;

    for (int banned : mst_idx)
    {
        rep(i, 0, n) make(i);
        double cur_log = 0;
        int cnt = 0;

        for (int id : ord)
        {
            if (id == banned) continue;

            int u = edges[id].second.first;
            int v = edges[id].second.second;

            if (find(u) != find(v))
            {
                Union(u, v);
                cur_log += edges[id].first;
                cnt++;
            }
        }

        if (cnt == n - 1 && cur_log > best_log)
        {
            second_log = min(second_log, cur_log);
        }
    }

    if (second_log > 9e99)
    {
        cout << -1 << nl;
        return;
    }

    // Convert log back to product
    ll result = llround(exp(second_log));
    cout << result << nl;
}
