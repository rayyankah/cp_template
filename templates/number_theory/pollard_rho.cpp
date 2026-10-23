// miller rabin (deterministic for 64-bit) + pollard rho factorization, ~n^(1/4) per factor
// isPrime64(n); factor(n) -> sorted list of prime factors with repetition
int mulmod(int a, int b, int m) { return (__int128)a * b % m; }
int powmod(int a, int e, int m)
{
    int r = 1 % m;
    a %= m;
    while (e) { if (e & 1) r = mulmod(r, a, m); a = mulmod(a, a, m); e >>= 1; }
    return r;
}
bool isPrime64(int n)
{
    if (n < 2) return false;
    for (int p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) if (n % p == 0) return n == p;
    int d = n - 1, s = 0;
    while (d % 2 == 0) d /= 2, s++;
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    {
        int x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool comp = true;
        rep(r, 1, s) { x = mulmod(x, x, n); if (x == n - 1) { comp = false; break; } }
        if (comp) return false;
    }
    return true;
}
int pollard(int n)
{
    if (n % 2 == 0) return 2;
    static mt19937_64 rg(12345);
    while (true)
    {
        int x = rg() % (n - 2) + 2, y = x, c = rg() % (n - 1) + 1, d = 1;
        auto f = [&](int v) { return (mulmod(v, v, n) + c) % n; };
        while (d == 1)
        {
            int prod = 1, sx = x, sy = y; // batch 64 gcds into one; remember the batch start
            rep(i, 0, 64)
            {
                x = f(x), y = f(f(y));
                int t = mulmod(prod, llabs(x - y), n);
                if (t == 0) { prod = 0; break; } // collided mod every factor: gcd(0, n) = n sends us to the fallback
                prod = t;
            }
            d = __gcd(prod, n);
            if (prod == 1 || d == n) // fall back to step-by-step, replaying this batch from its start
            {
                x = sx, y = sy, d = 1;
                while (d == 1) x = f(x), y = f(f(y)), d = __gcd(llabs(x - y), n);
            }
        }
        if (d != n) return d;
    }
}
void factorRec(int n, vi &out)
{
    if (n == 1) return;
    if (isPrime64(n)) { out.pb(n); return; }
    for (int p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
        if (n % p == 0) { out.pb(p); factorRec(n / p, out); return; }
    int d = pollard(n);
    factorRec(d, out), factorRec(n / d, out);
}
vi factor(int n) { vi f; factorRec(n, f); sort(all(f)); return f; }

vi getDivisors(int n)
{
    vi pf = factor(n);
    vi divs = {1};
    for (int i = 0; i < (int)pf.size(); )
    {
        int p = pf[i], cnt = 0;
        while (i < (int)pf.size() && pf[i] == p) cnt++, i++;
        int sz = divs.size();
        int pw = 1;
        rep(c, 0, cnt)
        {
            pw *= p;
            rep(j, 0, sz) divs.pb(divs[j] * pw);
        }
    }
    sort(all(divs)); // Optional: remove if you don't need them sorted
    return divs;
}

int phi(int n)
{
    vi pf = factor(n);
    pf.erase(unique(all(pf)), pf.end()); // Keep only distinct prime factors
    for (int p : pf) n = n / p * (p - 1);
    return n;
}
