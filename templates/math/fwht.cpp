// fast walsh hadamard transform (xor convolution)
// c = a xor-conv b: fwht(a,0), fwht(b,0), c[i] = a[i]*b[i], fwht(c,1)
void fwht(vi &a, bool inv)
{
    int n = a.size();
    for (int len = 1; len < n; len <<= 1)
        for (int i = 0; i < n; i += 2 * len)
            rep(j, i, i + len)
            {
                int u = a[j], v = a[j + len];
                a[j] = u + v, a[j + len] = u - v;
            }
    if (inv) for (auto &x : a) x /= n;
}
