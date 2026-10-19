// hopcroft karp bipartite matching, O(E sqrt V). HopcroftKarp hk(nL, nR); hk.add(l, r); hk.run()
// after run: ml[l] = matched right vertex or -1, mr[r] = matched left vertex or -1
struct HopcroftKarp
{
    int nL, nR;
    vvi g;
    vi ml, mr, dist;
    HopcroftKarp(int nL, int nR) : nL(nL), nR(nR), g(nL), ml(nL, -1), mr(nR, -1) {}
    void add(int l, int r) { g[l].pb(r); }
    bool bfs()
    {
        dist.assign(nL, -1);
        queue<int> q;
        rep(l, 0, nL) if (ml[l] == -1) dist[l] = 0, q.push(l);
        bool found = false;
        while (!q.empty())
        {
            int l = q.front(); q.pop();
            for (int r : g[l])
            {
                int l2 = mr[r];
                if (l2 == -1) found = true;
                else if (dist[l2] == -1) dist[l2] = dist[l] + 1, q.push(l2);
            }
        }
        return found;
    }
    bool dfs(int l)
    {
        for (int r : g[l])
        {
            int l2 = mr[r];
            if (l2 == -1 || (dist[l2] == dist[l] + 1 && dfs(l2))) { ml[l] = r, mr[r] = l; return true; }
        }
        dist[l] = -1;
        return false;
    }
    int run()
    {
        int res = 0;
        while (bfs()) rep(l, 0, nL) if (ml[l] == -1 && dfs(l)) res++;
        return res;
    }
};
