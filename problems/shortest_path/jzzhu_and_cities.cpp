//online:


//jjzzhu and cities - cf(add new path and if used);
 
//================ Code starts here ================
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vpi> adj(n + 1);
    vector<array<int,3>> roads;
    rep(i, 0, m)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
        roads.pb({u, v, w});
    }
 
    vpi temp;
    rep(i, 0, k)
    {
        int node, dis;
        cin >> node >> dis;
        temp.pb({dis, node});
        // add train edges to graph before Dijkstra
        adj[1].pb({node, dis});
        adj[node].pb({1, dis});
    }
 
    vector<long long> dist(n + 1, LLONG_MAX);
    dist[1] = 0;
    set<pair<long long,int>> s;
    s.insert({0, 1});
    vi visited(n + 1, 0);
    while (!s.empty())
    {
        auto yo = *s.begin();
        s.erase(s.begin());
        int u = yo.second;
        if (visited[u]) continue;
        visited[u] = 1;
        long long d = yo.first;
        for (auto &ele : adj[u])
        {
            int v = ele.first;
            long long wt = ele.second;
            if (!visited[v])
            {
                if (d + wt < dist[v])
                {
                    if (dist[v] != LLONG_MAX) s.erase({dist[v], v});
                    dist[v] = d + wt;
                    s.insert({dist[v], v});
                }
            }
        }
    }
 
    // count how many road-edges give the shortest distance for each node
    vi roadCount(n + 1, 0);
    for (auto &e : roads)
    {
        int u = e[0], v = e[1], w = e[2];
        if (dist[u] != LLONG_MAX && dist[u] + (long long)w == dist[v]) ++roadCount[v];
        if (dist[v] != LLONG_MAX && dist[v] + (long long)w == dist[u]) ++roadCount[u];
    }
 
    // used[node] == true means NO road provides shortest path (so a train must be kept)
    vector<bool> used(n + 1, false);
    for (int i = 1; i <= n; ++i) used[i] = (roadCount[i] == 0);
 
    int ans = 0;
    vi num(n + 1, 0);
    sort(all(temp));
    rep(i, 0, (int)temp.size()){
        int node = temp[i].second;
        int dis = temp[i].first;
        if (dist[node] == dis) num[node]++;
    }
    rep(i, 0, (int)temp.size()){
        int node = temp[i].second;
        int dis = temp[i].first;
        if (dist[node] < dis){
            ans++;
        }
        else if (dist[node] == dis && num[node] > 1 && used[node]){
            ans++;
            num[node]--;
        }
        else if (!used[node] && dist[node] == dis){
            ans++;
        }
    }
 
    cout << ans << nl;
}
