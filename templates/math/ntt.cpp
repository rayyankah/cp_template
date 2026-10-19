// ntt mod 998244353: multiply(a, b) returns the product polynomial
// example use: 103119A Accelerator (product of (1 + a_i x) by divide and conquer)
const int md = 998244353, ntt_root = 3;
void ntt(vi &a, bool inv)
{
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1)
    {
        int w = binExp(ntt_root, (md - 1) / len, md);
        if (inv) w = binExp(w, md - 2, md);
        for (int i = 0; i < n; i += len)
        {
            int wn = 1;
            rep(j, 0, len / 2)
            {
                int u = a[i + j], v = a[i + j + len / 2] * wn % md;
                a[i + j] = (u + v) % md, a[i + j + len / 2] = (u - v + md) % md;
                wn = wn * w % md;
            }
        }
    }
    if (inv)
    {
        int ninv = binExp(n, md - 2, md);
        for (auto &x : a) x = x * ninv % md;
    }
}
vi multiply(vi a, vi b)
{
    int need = a.size() + b.size() - 1, n = 1;
    while (n < need) n <<= 1;
    if (min(a.size(), b.size()) < 32) // small: plain multiplication
    {
        vi c(need, 0);
        rep(i, 0, (int)a.size()) rep(j, 0, (int)b.size()) c[i + j] = (c[i + j] + a[i] * b[j]) % md;
        return c;
    }
    a.resize(n), b.resize(n);
    ntt(a, false), ntt(b, false);
    rep(i, 0, n) a[i] = a[i] * b[i] % md;
    ntt(a, true);
    a.resize(need);
    return a;
}
