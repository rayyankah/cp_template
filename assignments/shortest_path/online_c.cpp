//c online: 
struct edge
{
    int u;
    int v;
    int wt;
    int idx;
};

//================ Code starts here ================
void solve()
{
    int n, m, p;
    cin >> n >> m >> p;
    rep(i, 0, n)
    {
        make(i);
    }
    int k;
    cin >> k;
    mii mp;
    rep(i, 0, k)
    {
        int idxx;
        cin >> idxx;
        mp[idxx] = 1;
    }
    // debug(prob);
    vector<edge> edges(m);
    rep(i, 0, m)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].wt;
        edges[i].idx = i;
    }
    sort(all(edges), [&](edge a, edge b)
         { return a.wt < b.wt; });
    ll ans = 0;
    vpi fin_edges;
    rep(i, 0, m)
    {
        int uu = edges[i].u;
        int vvv = edges[i].v;
        ll wtt = edges[i].wt;
        if (find(uu) != find(vvv) && (mp.find(uu) == mp.end()) && (mp.find(vvv) == mp.end()))
        {
            Union(uu, vvv);
            fin_edges.pb({uu, vvv});
            ans += wtt;
            edges[i].wt = INT_MAX;
        }
    }
    int con = 0;

    rep(i, 0, n)
    {
        if (mp.find(i) != mp.end())
            continue;
        if (par[i] == i)
            con++;
    }
    if (con == 1)
    {
        int sz = (int)fin_edges.size();
        cout << sz << nl;

        // cout << "Total weight " << ans << nl;
        rep(i, 0, (int)fin_edges.size())
        {
            cout << fin_edges[i].first << " " << fin_edges[i].second << nl;
        }
        cout << ans << nl;
        return;
    }
    rep(i, 0, m)
    {
        bool flag1 = false;
        bool flag2 = false;
        int uu = edges[i].u;
        int vvv = edges[i].v;
        int wtt = edges[i].wt;
        int idxx = edges[i].idx;
        if (mp.find(uu) != mp.end())
            flag1 = true;
        if (mp.find(vvv) != mp.end())
            flag2 = true;
        if (!flag1 && !flag2)
            continue;
        if (flag1 && flag2)
        {
            edges[i].wt = wtt + 2 * p;
        }
        else
        {
            edges[i].wt = wtt + p;
        }
    }
    sort(all(edges), [&](edge a, edge b)
         { return a.wt < b.wt; });

    // Track which components contain safe nodes
    vi compHasSafe(n, 0);
    rep(i, 0, n)
    {
        if (find(i) == i && mp.find(i) == mp.end())
        {
            compHasSafe[i] = 1;
        }
    }

    rep(i, 0, m)
    {
        int uu = edges[i].u;
        int vvv = edges[i].v;

        int rootU = find(uu);
        int rootV = find(vvv);

        if (rootU == rootV)
            continue;

        bool flag1 = (mp.find(uu) != mp.end());
        bool flag2 = (mp.find(vvv) != mp.end());

        // Skip safe-safe edges (already processed in pass 1 or redundant)
        if (!flag1 && !flag2)
            continue;

        // If this edge merges two components that BOTH contain safe nodes,
        // we reduce the number of disconnected safe components.
        if (compHasSafe[rootU] && compHasSafe[rootV])
            con--;

        Union(uu, vvv);
        ans += edges[i].wt;
        fin_edges.pb({uu, vvv});

        // Update safe status for the new root
        int newRoot = find(uu);
        compHasSafe[newRoot] = compHasSafe[rootU] | compHasSafe[rootV];

        // If all safe nodes are connected, stop immediately to minimize cost
        if (con == 1)
            break;
    }

    if (con > 1)
    {
        cout << -1 << nl;
        return;
    }
    int sz = (int)fin_edges.size();
    cout << sz << nl;

    // cout << "Total weight " << ans << nl;
    rep(i, 0, (int)fin_edges.size())
    {
        cout << fin_edges[i].first << " " << fin_edges[i].second << nl;
    }
    cout << ans << nl;
}

signed main()
{
    fast;
    // #ifndef ONLINE_JUDGE
    //     freopen("input/test10.txt", "r", stdin);
    // // freopen("output.txt", "w", stdout);
    // #endif

    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
