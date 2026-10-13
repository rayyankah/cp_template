// ntt for any ntt-friendly prime (root 3) + exact convolution of non-negative values using two primes and crt
// conv(a, b) is exact while every result is below about 4e17
void ntt(vi &a, bool inv, int md)
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
        int w = binExp(3, (md - 1) / len, md);
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
vi conv(vi a, vi b)
{
    const int m1 = 998244353, m2 = 469762049;
    int need = a.size() + b.size() - 1, n = 1;
    while (n < need) n <<= 1;
    vi r1, r2;
    for (int md : {m1, m2})
    {
        vi x = a, y = b;
        x.resize(n), y.resize(n);
        ntt(x, false, md), ntt(y, false, md);
        rep(i, 0, n) x[i] = x[i] * y[i] % md;
        ntt(x, true, md);
        (md == m1 ? r1 : r2) = x;
    }
    vi res(need);
    int inv = binExp(m1 % m2, m2 - 2, m2);
    rep(i, 0, need) res[i] = r1[i] + (r2[i] - r1[i] % m2 + m2) % m2 * inv % m2 * m1;
    return res;
}
