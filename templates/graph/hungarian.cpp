// hungarian algorithm: min cost assignment, a is 1-indexed n x m with n <= m, O(n^2 m)
// for max cost, negate the matrix
int hungarian(vvi &a, int n, int m, vi &ans)
{
    vi u(n + 1), v(m + 1), p(m + 1), way(m + 1);
    rep(i, 1, n + 1)
    {
        p[0] = i;
        int j0 = 0;
        vi minv(m + 1, LLONG_MAX);
        vector<char> used(m + 1, 0);
        do
        {
            used[j0] = 1;
            int i0 = p[j0], delta = LLONG_MAX, j1 = 0;
            rep(j, 1, m + 1) if (!used[j])
            {
                int cur = a[i0][j] - u[i0] - v[j];
                if (cur < minv[j]) minv[j] = cur, way[j] = j0;
                if (minv[j] < delta) delta = minv[j], j1 = j;
            }
            rep(j, 0, m + 1)
            {
                if (used[j]) u[p[j]] += delta, v[j] -= delta;
                else minv[j] -= delta;
            }
            j0 = j1;
        } while (p[j0] != 0);
        do
        {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    ans.assign(n + 1, 0);
    rep(j, 1, m + 1) ans[p[j]] = j;
    return -v[0];
}
