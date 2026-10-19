// catalan numbers C_n = C(2n, n) / (n + 1), O(1) each after compute_factorials() (needs 2n < N)
int catalanNum(int n) { return ncr(2 * n, n) * binExp(n + 1, MOD - 2) % MOD; }
// table for small n with any modulus (no inverses), O(n^2)
vi catalanTable(int n, int m = MOD)
{
    vi c(n + 1, 0);
    c[0] = 1;
    rep(i, 1, n + 1) rep(j, 0, i) c[i] = (c[i] + c[j] * c[i - 1 - j]) % m;
    return c;
}
