void solve_directed_apsp() {
    int n, m, q;
    cin >> n >> m >> q;

    const long long INF = (long long)4e18;
    vector<vector<long long>> dist(n+1, vector<long long>(n+1, INF));
    for(int i=1;i<=n;i++) dist[i][i]=0;

    for(int i=0;i<m;i++){
        int u,v; long long w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w); // no dist[v][u]
    }

    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++){
            if(dist[i][k]>=INF/2) continue;
            for(int j=1;j<=n;j++){
                if(dist[k][j]>=INF/2) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }

    while(q--){
        int u,v; cin >> u >> v;
        cout << (dist[u][v]>=INF/2? -1 : dist[u][v]) << "\n";
    }
} 
