//the queue
// const int N = 1005;
vvi adj(N);
vi dp(N);
vi subtree_size(N);
void dfs(int u, int p){
    int i =u;
    subtree_size[u] = 0;
    dp[u]=1;
    for(auto &v: adj[u]){
        if(v==p)continue;
        dfs(v,u);
        dp[i] = binMul(dp[i], dp[v], MOD);
        dp[i] = binMul(dp[i], inv[subtree_size[v]], MOD);
        dp[i]%=MOD;
        subtree_size[u]+=subtree_size[v];

    }
    dp[i]= binMul(dp[i], factorial[subtree_size[u]], MOD);
    subtree_size[u]++;
}

//================ Code starts here ================
void solve()
{
    int n;
    cin >> n;
    vi indeg(n + 1, 0);
    rep(i, 0, n - 1) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
        indeg[v]++;
    }
    // finding root (ceo of the company)
    int root = -1;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            root = i;
            break;
        }
    }
    dfs(root, -1);
    cout << dp[root] << nl;
}
signed main()
{
    fast;
    compute_factorials();
    int t = 1;
    cin >> t;
    int cas = 1;
    while (t--)
    {
        cout << "Case " << cas << ": ";
        // clear adj, dp, subtree_size for each test case
        for (int i = 1; i <= 1000; i++) {
            adj[i].clear();
            dp[i] = 0;
            subtree_size[i] = 0;
        }
        solve();
        cas++;
    }
}  
