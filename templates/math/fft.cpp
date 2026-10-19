// fft with complex doubles: exact integer convolution while results stay below ~1e15 (n up to ~1e6 with small values)
// multiplying huge numbers: put digits in a, b, convolve, then carry
typedef complex<double> cd;
void fft(vector<cd> &a, bool inv)
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
        double ang = 2 * acos(-1.0) / len * (inv ? -1 : 1);
        cd wl(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len)
        {
            cd w(1);
            rep(j, 0, len / 2)
            {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v, a[i + j + len / 2] = u - v;
                w *= wl;
            }
        }
    }
    if (inv) for (auto &x : a) x /= n;
}
vi convolve(const vi &a, const vi &b)
{
    if (a.empty() || b.empty()) return {};
    int n = 1;
    while (n < (int)(a.size() + b.size())) n <<= 1;
    vector<cd> fa(all(a)), fb(all(b));
    fa.resize(n), fb.resize(n);
    fft(fa, false), fft(fb, false);
    rep(i, 0, n) fa[i] *= fb[i];
    fft(fa, true);
    vi res(a.size() + b.size() - 1);
    rep(i, 0, (int)res.size()) res[i] = llround(fa[i].real());
    return res;
}
