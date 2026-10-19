// lagrange interpolation: y[i] = f(i) for i = 0..k (f has degree <= k), returns f(x) mod MOD in O(k)
// needs fact / invFact (compute_factorials) with k < N. example: sum of i^p for i <= n is a degree p+1 polynomial
int lagrange(const vi &y, int x)
{
    int k = y.size() - 1;
    x %= MOD;
    if (x >= 0 && x <= k) return y[x];
    vi pre(k + 2, 1), suf(k + 2, 1);
    rep(i, 0, k + 1) pre[i + 1] = pre[i] * ((x - i) % MOD + MOD) % MOD;
    repb(i, k, 0) suf[i] = suf[i + 1] * ((x - i) % MOD + MOD) % MOD;
    int res = 0;
    rep(i, 0, k + 1)
    {
        int t = y[i] * pre[i] % MOD * suf[i + 1] % MOD * invFact[i] % MOD * invFact[k - i] % MOD;
        res = ((k - i) & 1) ? (res - t + MOD) % MOD : (res + t) % MOD;
    }
    return res;
}
