// linear sieve up to n: primes, smallest prime factor, mobius mu, euler phi in O(n)
vi lp, primesL, muL, phiL;
void linearSieve(int n)
{
    lp.assign(n + 1, 0), muL.assign(n + 1, 0), phiL.assign(n + 1, 0), primesL.clear();
    muL[1] = 1, phiL[1] = 1;
    rep(i, 2, n + 1)
    {
        if (!lp[i]) lp[i] = i, primesL.pb(i), muL[i] = -1, phiL[i] = i - 1;
        for (int p : primesL)
        {
            if (p > lp[i] || i * p > n) break;
            lp[i * p] = p;
            if (p == lp[i]) { muL[i * p] = 0, phiL[i * p] = phiL[i] * p; }
            else { muL[i * p] = -muL[i], phiL[i * p] = phiL[i] * (p - 1); }
        }
    }
}
// segmented sieve: primes in [L, R], R up to ~1e12 with R - L up to ~1e7
vi segmentedSieve(int L, int R)
{
    int lim = sqrtl((long double)R) + 1;
    vector<char> small(lim + 1, 1), mark(R - L + 1, 1);
    vi res;
    for (int i = 2; i <= lim; i++)
    {
        if (!small[i]) continue;
        for (int j = i * i; j <= lim; j += i) small[j] = 0;
        for (int j = max(i * i, (L + i - 1) / i * i); j <= R; j += i) mark[j - L] = 0;
    }
    rep(i, max(L, 2LL), R + 1) if (mark[i - L]) res.pb(i);
    return res;
}
