// floor blocks: floor(n / i) takes only O(sqrt n) different values. loop over blocks [l, r] with the same q
// sum_{i=1..n} f(i) * g(n / i): for (l, r, q) in blocks add (F(r) - F(l-1)) * g(q), F = prefix sum of f
// example: sum_{i=1..n} n / i  in O(sqrt n)
int sumFloor(int n)
{
    int s = 0;
    for (int l = 1, r; l <= n; l = r + 1)
    {
        int q = n / l;
        r = n / q;            // last i with n / i == q
        s += (r - l + 1) * q; // all i in [l, r] give the same q
    }
    return s;
}
// ceil blocks: ceil(n / i) for i = 1..n-1: q = (n + l - 1) / l, r = (n - 1) / (q - 1) when q > 1
// count of x in [1, R] coprime to d: inclusion-exclusion over distinct primes of d (d up to 1e12+: get
// them with pollard_rho.cpp factor(), or trial division up to sqrt(d)). at most 15 primes for d <= 1e18
int coprimeCount(int R, const vi &ps) // ps = distinct primes of d
{
    int k = ps.size(), res = 0;
    rep(mask, 0, 1LL << k)
    {
        int prod = 1, bits = 0;
        bool over = false;
        rep(j, 0, k) if (mask >> j & 1) { bits++; if (prod > R / ps[j]) { over = true; break; } prod *= ps[j]; }
        if (over) continue;
        res += (bits % 2 ? -1 : 1) * (R / prod);
    }
    return res; // count in [L, R] = coprimeCount(R) - coprimeCount(L - 1)
}
vi distinctPrimes(int d) { vi ps; for (int p = 2; p * p <= d; p++) if (d % p == 0) { ps.pb(p); while (d % p == 0) d /= p; } if (d > 1) ps.pb(d); return ps; }
// floor sum: sum_{i=0}^{n-1} floor((a*i + b) / m), n >= 0, m >= 1, a, b >= 0, O(log). lattice points under a line
int floorSum(int n, int m, int a, int b)
{
    int ans = 0;
    while (true)
    {
        if (a >= m) ans += (n - 1) * n / 2 * (a / m), a %= m;
        if (b >= m) ans += n * (b / m), b %= m;
        int y = a * n + b;
        if (y < m) break;
        n = y / m, b = y % m, swap(m, a);
    }
    return ans;
}
