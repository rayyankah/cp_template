// tweaks: 

void solve_restricted_intermediate() {
    int n, m, q;
    cin >> n >> m >> q;

    const long long INF = (long long)4e18;
    vector<vector<long long>> dist(n+1, vector<long long>(n+1, INF));
    for(int i=1;i<=n;i++) dist[i][i]=0;

    for(int i=0;i<m;i++){
        int u,v; long long w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }

    // bucket queries by k
    struct Query{int u,v,idx;};
    vector<vector<Query>> bucket(n+1);
    vector<long long> ans(q);

    for(int i=0;i<q;i++){
        int u,v,k; 
        cin >> u >> v >> k;
        if(k<0) k=0;
        if(k>n) k=n;
        bucket[k].push_back({u,v,i});
    }

    // k = 0 answers (no intermediates) means direct edges only (dist already has direct best)
    for(auto &qq: bucket[0]){
        long long d = dist[qq.u][qq.v];
        ans[qq.idx] = (d>=INF/2? -1 : d);
    }

    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            if(dist[i][k]>=INF/2) continue;
            for(int j=1;j<=n;j++){
                if(dist[k][j]>=INF/2) continue;
                long long nd = dist[i][k] + dist[k][j];
                if(nd < dist[i][j]) dist[i][j] = nd;
            }
        }
        for(auto &qq: bucket[k]){
            long long d = dist[qq.u][qq.v];
            ans[qq.idx] = (d>=INF/2? -1 : d);
        }
    }

    for(int i=0;i<q;i++) cout << ans[i] << "\n";
} 
