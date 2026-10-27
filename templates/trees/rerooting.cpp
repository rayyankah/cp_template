// rerooting dp: answer for EVERY root in O(n). example: sum of distances from each vertex to all others
// step 1: dfs from root 0, down[v] = answer inside v's subtree (here: sum of depths below v), sz[v]
// step 2: top-down, ans[child] from ans[parent]: moving the root from p to c, the sz[c] vertices of c's
//         subtree get 1 closer and the other n - sz[c] get 1 farther: ans[c] = ans[p] - sz[c] + (n - sz[c])
// to adapt: change what down[] stores and the formula that moves the root across one edge
vi rerootSumDist(const vvi &g) // vertices 0..n-1
{
    int n = g.size();
    vi par(n, -1), order, sz(n, 1), down(n, 0), ans(n, 0);
    order.pb(0), par[0] = 0;
    rep(i, 0, n) for (int u : g[order[i]]) if (u != par[order[i]]) par[u] = order[i], order.pb(u); // bfs order
    par[0] = -1;
    repb(i, n - 1, 1) { int v = order[i], p = par[v]; sz[p] += sz[v], down[p] += down[v] + sz[v]; } // bottom-up
    ans[0] = down[0];
    rep(i, 1, n) { int v = order[i]; ans[v] = ans[par[v]] - sz[v] + (n - sz[v]); } // top-down
    return ans;
}
