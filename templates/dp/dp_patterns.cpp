// common dp patterns (LIS is in misc/common.cpp: lis(a))

// 0/1 knapsack, max value with weight <= W, O(nW). loop w DOWN so each item is used once (UP = unlimited items)
int knapsack(const vi &wt, const vi &val, int W)
{
    vi dp(W + 1, 0);
    rep(i, 0, (int)wt.size()) repb(w, W, wt[i]) dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    return dp[W];
}
// subset sum reachability with bitset, O(n S / 64). which sums of a subset are possible
const int MAXS = 100001;
bitset<MAXS> subsetSums(const vi &a) { bitset<MAXS> b; b[0] = 1; for (int x : a) b |= b << x; return b; }
// count ways to reach each sum (mod MOD), each item once
vi countSubsetSums(const vi &a, int S)
{
    vi dp(S + 1, 0);
    dp[0] = 1;
    for (int x : a) repb(s, S, x) dp[s] = (dp[s] + dp[s - x]) % MOD;
    return dp;
}
// bitmask dp, travelling salesman: dp[mask][v] = min cost to visit mask, ending at v, start at 0. O(2^n n^2), n <= 20
int tsp(const vvi &c) // c[u][v] cost, returns min cost of a cycle through all vertices from 0
{
    int n = c.size();
    vvi dp(1LL << n, vi(n, LLONG_MAX / 4));
    dp[1][0] = 0;
    rep(mask, 1, 1LL << n) rep(v, 0, n) if ((mask >> v & 1) && dp[mask][v] < LLONG_MAX / 4)
        rep(u, 0, n) if (!(mask >> u & 1)) dp[mask | (1LL << u)][u] = min(dp[mask | (1LL << u)][u], dp[mask][v] + c[v][u]);
    int best = LLONG_MAX;
    rep(v, 0, n) best = min(best, dp[(1LL << n) - 1][v] + c[v][0]);
    return best;
}
// interval dp: dp[l][r] from smaller intervals. loop by length. example: merge stones, cost = sum of the merged part
int mergeCost(const vi &a)
{
    int n = a.size();
    vi pre(n + 1, 0);
    rep(i, 0, n) pre[i + 1] = pre[i] + a[i];
    vvi dp(n, vi(n, 0));
    rep(len, 2, n + 1) rep(l, 0, n - len + 1)
    {
        int r = l + len - 1;
        dp[l][r] = LLONG_MAX;
        rep(k, l, r) dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + pre[r + 1] - pre[l]);
    }
    return dp[0][n - 1];
}
// longest common subsequence O(nm)
int lcs(const string &a, const string &b)
{
    int n = a.size(), m = b.size();
    vvi dp(n + 1, vi(m + 1, 0));
    rep(i, 1, n + 1) rep(j, 1, m + 1) dp[i][j] = a[i - 1] == b[j - 1] ? dp[i - 1][j - 1] + 1 : max(dp[i - 1][j], dp[i][j - 1]);
    return dp[n][m];
}
// max subarray sum (kadane), non-empty
int kadane(const vi &a) { int best = LLONG_MIN, cur = 0; for (int x : a) cur = max(x, cur + x), best = max(best, cur); return best; }
// dp over a path split into k blocks with cost(l, r): dp[j][i] = min over p of dp[j-1][p] + cost(p, i-1). O(k n^2)
// if cost is "sum |x - median|" of a sorted block: median m = (l + r) / 2, use prefix sums of x
