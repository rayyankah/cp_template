// classic string dps
// edit distance (insert / delete / replace, cost 1 each), O(nm)
int editDistance(const string &a, const string &b)
{
    int n = a.size(), m = b.size();
    vvi d(n + 1, vi(m + 1));
    rep(i, 0, n + 1) d[i][0] = i;
    rep(j, 0, m + 1) d[0][j] = j;
    rep(i, 1, n + 1) rep(j, 1, m + 1)
        d[i][j] = min({d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (a[i - 1] != b[j - 1])});
    return d[n][m];
}
// longest common subsequence, returns one LCS string
string lcsString(const string &a, const string &b)
{
    int n = a.size(), m = b.size();
    vvi d(n + 1, vi(m + 1, 0));
    repb(i, n - 1, 0) repb(j, m - 1, 0) d[i][j] = a[i] == b[j] ? d[i + 1][j + 1] + 1 : max(d[i + 1][j], d[i][j + 1]);
    string res;
    int i = 0, j = 0;
    while (i < n && j < m)
    {
        if (a[i] == b[j]) res += a[i], i++, j++;
        else if (d[i + 1][j] >= d[i][j + 1]) i++;
        else j++;
    }
    return res;
}
// number of distinct subsequences (including the empty one) mod MOD, O(n)
int distinctSubsequences(const string &s)
{
    vi last(256, -1);
    int n = s.size();
    vi dp(n + 1);
    dp[0] = 1;
    rep(i, 1, n + 1)
    {
        unsigned char c = s[i - 1];
        dp[i] = dp[i - 1] * 2 % MOD;
        if (last[c] != -1) dp[i] = (dp[i] - dp[last[c]] + MOD) % MOD;
        last[c] = i - 1;
    }
    return dp[n];
}
