//b sec online

void solve()
{
    int m, h;
    cin >> m >> h;
    float r;
    cin >> r;
    vector<pair<float, float>> mice(m);
    rep(i, 0, m)
    {
        cin >> mice[i].first >> mice[i].second;
    }
    vector<pair<float, float>> holes(h);
    vi holecpa(h, 0);
    rep(i, 0, h)
    {
        cin >> holes[i].first >> holes[i].second;
        cin>>holecpa[i];
    }
    vvi adj(h + m + 2);
    vvi capacity(h + m + 2, vi(h + m + 2, 0));
    vvi original(h + m + 2, vi(h + m + 2, 0));

    rep(i, 0, m)
    {
        rep(j, 0, h)
        {
            float x1 = mice[i].first;
            float y1 = mice[i].second;
            float x2 = holes[j].first;
            float y2 = holes[j].second;
            float diffval = diff(x1, y1, x2, y2);
            if (diffval <= r)
            {
                adj[i].pb(j + m);
                adj[j + m].pb(i);
                capacity[i][j + m] = 1;
                original[i][j + m] = 1;
            }
        }
    }
    int flow = 0;
    int s = m + h;
    int t = m + h + 1;
    rep(i, 0, m)
    {
        adj[i].pb(s);
        adj[s].pb(i);
        capacity[s][i] = 1;
        original[s][i] = 1;
    }
    rep(i, 0, h)
    {
        int j = i + m;
        adj[j].pb(t);
        adj[t].pb(j);
        capacity[j][t] += holecpa[i];
        // original[j][t] += 1;
    }
    while (true)
    {
        vi par(m + h + 2, -1);
        par[s] = -2;
        queue<pi> q;
        const int INF = 1e18;
        q.push({s, INF});
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
                    if (child == t)
                    {
                        tfound = true;
                        flow += new_flow;
                        int currv = child;

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
    cout << flow << nl;
}
