// b online
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vi st(n + 1);
    vi tar(n + 1);
    rep(i, 1, n + 1)
    {
        cin >> st[i];
    }
    rep(i, 1, n + 1)
    {
        cin >> tar[i];
    }
    int INF = LLONG_MAX;
    vvi dist(n + 1, vi(n + 1, INF));
    rep(i, 0, m)
    {
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = w;
    }
    rep(i, 1, n + 1)
    {
        dist[i][i] = 0;
    }
    rep(k,1,n+1){
        rep(i,1,n+1){
            rep(j,1,n+1){
                int dd = dist[i][k];
                int dd2 = dist[k][j];
                if(dd!=INF && dd2!=INF){
                    dist[i][j]=min<ll>(dist[i][j],dd+dd2);
                }
            }
        }
    }
    vi ans;
    rep(i,1,n+1){
        if(dist[st[i]][tar[i]]!=INF){
            ans.pb(dist[st[i]][tar[i]]);
        }
    }
    
    sort(all(ans),greater<int>());
    int sz = (int)ans.size();
    int sum =0;
    int i=0;
    int now =0;
    int ct = 0;
    // debug(dist[4][3],st[1],tar[1]);
    while(i<sz){
        int mul = (1<<now);
        sum+=ans[i]*mul;
        ct++;
        if(ct==k){
            ct=0;
            now++;
        }
        i++;
    }
    cout<<sum<<nl;
}
