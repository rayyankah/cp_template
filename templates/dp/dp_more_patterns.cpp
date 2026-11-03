// more dp patterns: bounded knapsack, counting increasing subsequences, distinct subsequences,
// pattern automaton dp, broken profile, SOS over supermasks, AND = 0 subsets, meet in the middle

// ---------- bounded knapsack: item i has cnt[i] copies, binary bundles 1, 2, 4, ..., rest ----------
// max value with weight <= W. O(W * sum log cnt)
int boundedKnapsack(const vi &wt, const vi &val, const vi &cnt, int W)
{
    vi dp(W + 1, 0);
    rep(i, 0, (int)wt.size())
        for (int b = 1, left = cnt[i]; left > 0; b *= 2)
        {
            int t = min(b, left), w = t * wt[i], v = t * val[i];
            left -= t;
            for (int c = W; c >= w; c--) dp[c] = max(dp[c], dp[c - w] + v);
        }
    return dp[W];
}

// ---------- number of strictly increasing subsequences (mod MOD), sum segment tree over values ----------
int countIncreasing(const vi &a)
{
    vi v = a;
    sort(all(v));
    v.erase(unique(all(v)), v.end());
    int m = v.size(), total = 0;
    vi t(2 * m, 0);
    for (int x : a)
    {
        int k = lower_bound(all(v), x) - v.begin(), s = 0;
        for (int l = m, r = m + k; l < r; l /= 2, r /= 2)   // sum over values < x
        {
            if (l & 1) s += t[l++];
            if (r & 1) s += t[--r];
        }
        int ways = (1 + s) % MOD;
        total = (total + ways) % MOD;
        for (int p = k + m; p >= 1; p /= 2) t[p] = (t[p] + ways) % MOD;
    }
    return total;
}

// ---------- distinct subsequences of each length: cnt[len] (capped at CAP) ----------
vi distinctSubseqByLength(const string &s, int CAP = (int)2e18)
{
    int n = s.size();
    vvi dp(n + 1, vi(n + 1, 0));
    rep(i, 0, n + 1) dp[i][0] = 1;
    vi last(256, -1);
    rep(i, 1, n + 1)
    {
        int c = (unsigned char)s[i - 1];
        rep(j, 1, n + 1)
        {
            dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1] - (last[c] != -1 ? dp[last[c]][j - 1] : 0);
            dp[i][j] = min(dp[i][j], CAP);
        }
        last[c] = i - 1;
    }
    return dp[n];
}

// ---------- strings of length n over A-Z that avoid pattern p (KMP automaton dp), mod MOD ----------
// contain = 26^n - avoid. for "contains", alternatively add an absorbing state m
int avoidPattern(int n, const string &p)
{
    int m = p.size();
    vi fail(m, 0);
    rep(i, 1, m)
    {
        int j = fail[i - 1];
        while (j && p[i] != p[j]) j = fail[j - 1];
        if (p[i] == p[j]) j++;
        fail[i] = j;
    }
    vvi go(m, vi(26));
    rep(j, 0, m) rep(c, 0, 26) go[j][c] = (p[j] - 'A' == c) ? j + 1 : (j ? go[fail[j - 1]][c] : 0);
    vi dp(m, 0), nd(m);
    dp[0] = 1;
    rep(step, 0, n)
    {
        fill(all(nd), 0);
        rep(j, 0, m) if (dp[j]) rep(c, 0, 26) if (go[j][c] < m) nd[go[j][c]] = (nd[go[j][c]] + dp[j]) % MOD;
        swap(dp, nd);
    }
    int s = 0;
    for (int x : dp) s = (s + x) % MOD;
    return s;
}

// ---------- broken profile: domino tilings of an n x m grid (n <= 10), mod MOD ----------
int countTilings(int n, int m)
{
    int full = 1 << n;
    vi dp(full, 0), nd(full);
    dp[0] = 1;
    rep(col, 0, m) rep(r, 0, n)
    {
        fill(all(nd), 0);
        rep(mask, 0, full)
        {
            int v = dp[mask];
            if (!v) continue;
            if (mask >> r & 1) { nd[mask ^ (1 << r)] = (nd[mask ^ (1 << r)] + v) % MOD; continue; }
            if (col + 1 < m) nd[mask | (1 << r)] = (nd[mask | (1 << r)] + v) % MOD;           // horizontal
            if (r + 1 < n && !(mask >> (r + 1) & 1)) nd[mask | (1 << (r + 1))] = (nd[mask | (1 << (r + 1))] + v) % MOD; // vertical
        }
        swap(dp, nd);
    }
    return dp[0];
}

// ---------- SOS over supermasks: f[mask] = sum of a[sup] over all supermasks sup of mask ----------
void sosSuper(vi &f, int B)
{
    rep(b, 0, B) rep(mask, 0, 1 << B)
        if (!(mask >> b & 1)) f[mask] += f[mask | (1 << b)];
}
// non-empty subsets with AND == 0 (values < 2^B), inclusion-exclusion over the bits kept by the AND
int countAndZero(const vi &a, int B)
{
    vi f(1 << B, 0);
    for (int x : a) f[x]++;
    sosSuper(f, B);
    int ans = 0;
    rep(mask, 0, 1 << B)
    {
        int w = (binExp(2, f[mask]) - 1 + MOD) % MOD;
        ans = (__builtin_popcountll(mask) & 1) ? (ans - w + MOD) % MOD : (ans + w) % MOD;
    }
    return ans;
}

// ---------- meet in the middle: subsets with sum exactly x (n <= 40) ----------
int countSubsetSum(const vi &t, int x)
{
    int n = t.size(), h = n / 2;
    auto sums = [&](int l, int r)
    {
        vi s = {0};
        rep(i, l, r) { int k = s.size(); rep(j, 0, k) s.pb(s[j] + t[i]); }
        return s;
    };
    vi A = sums(0, h), B = sums(h, n);
    sort(all(B));
    int ans = 0;
    for (int v : A) ans += upper_bound(all(B), x - v) - lower_bound(all(B), x - v);
    return ans;
}
