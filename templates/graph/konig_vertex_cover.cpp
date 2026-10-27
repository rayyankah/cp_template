// minimum vertex cover in a bipartite graph = maximum matching (konig), WITH the actual cover vertices
// left 0..nL-1, right 0..nR-1, adj[l] = right neighbours. also gives max independent set = all - cover
// cover = (left vertices NOT reached) + (right vertices reached) by alternating paths from free left vertices
struct Konig
{
    int nL, nR;
    vvi adj;
    vi ml, mr; // ml[l] = matched right or -1, mr[r] = matched left or -1
    vector<bool> seen;
    Konig(int nL, int nR) : nL(nL), nR(nR), adj(nL), ml(nL, -1), mr(nR, -1) {}
    void add(int l, int r) { adj[l].pb(r); }
    bool kuhn(int v)
    {
        for (int r : adj[v]) if (!seen[r])
        {
            seen[r] = true;
            if (mr[r] < 0 || kuhn(mr[r])) { ml[v] = r, mr[r] = v; return true; }
        }
        return false;
    }
    int matching()
    {
        int res = 0;
        rep(v, 0, nL) { seen.assign(nR, false); if (kuhn(v)) res++; }
        return res;
    }
    pair<vi, vi> cover() // call after matching(). {left vertices, right vertices} of a minimum cover
    {
        vector<bool> visL(nL, false), visR(nR, false);
        vi q;
        rep(v, 0, nL) if (ml[v] < 0) visL[v] = true, q.pb(v);
        rep(i, 0, (int)q.size())
        {
            int v = q[i];
            for (int r : adj[v]) if (!visR[r] && ml[v] != r) // go along a non-matching edge
            {
                visR[r] = true;
                int l = mr[r];
                if (l >= 0 && !visL[l]) visL[l] = true, q.pb(l); // come back along the matching edge
            }
        }
        vi L, R;
        rep(v, 0, nL) if (!visL[v]) L.pb(v);
        rep(r, 0, nR) if (visR[r]) R.pb(r);
        return {L, R};
    }
};
