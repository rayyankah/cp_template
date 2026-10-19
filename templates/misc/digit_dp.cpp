// digit dp skeleton: count x in [0, N] with some digit property (example: digit sum == S)
// count(R) - count(L - 1) for a range. memo over (pos, state) only when not tight
string digs;
int S;
int memo[20][200];
bool seen[20][200];
int go(int pos, int sum, bool tight)
{
    if (sum > S) return 0;
    if (pos == (int)digs.size()) return sum == S;
    if (!tight && seen[pos][sum]) return memo[pos][sum];
    int lim = tight ? digs[pos] - '0' : 9, res = 0;
    rep(d, 0, lim + 1) res += go(pos + 1, sum + d, tight && d == lim);
    if (!tight) seen[pos][sum] = 1, memo[pos][sum] = res;
    return res;
}
int countUpTo(int N) // numbers in [0, N] with digit sum S
{
    if (N < 0) return 0;
    digs = to_string(N);
    memset(seen, 0, sizeof seen);
    return go(0, 0, true);
}
// add a "started" flag to the state when leading zeros matter
