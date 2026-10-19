// pattern matching with wildcards '?' (in text and/or pattern) using fft (needs math/fft.cpp: convolve)
// position i matches iff sum over j of p_j t_{i+j} (p_j - t_{i+j})^2 = 0, with '?' = 0 and letters = 1..26
// = sum p^3 t - 2 p^2 t^2 + p t^3 -> three convolutions. returns all i where pat matches text at i
vi wildcardMatch(const string &text, const string &pat)
{
    int n = text.size(), m = pat.size();
    if (m > n) return {};
    auto v = [](char c) { return c == '?' ? 0LL : (int)(c - 'a' + 1); };
    vi t1(n), t2(n), t3(n), p1(m), p2(m), p3(m);
    rep(i, 0, n) { int x = v(text[i]); t1[i] = x, t2[i] = x * x, t3[i] = x * x * x; }
    rep(j, 0, m) { int x = v(pat[m - 1 - j]); p1[j] = x, p2[j] = x * x, p3[j] = x * x * x; } // reversed
    vi a = convolve(p3, t1), b = convolve(p2, t2), c = convolve(p1, t3);
    vi res;
    rep(i, 0, n - m + 1) if (a[i + m - 1] - 2 * b[i + m - 1] + c[i + m - 1] == 0) res.pb(i);
    return res;
}
// letters only up to 26: values reach 26^4 * m, fine for doubles while m <= ~2e5. for bigger inputs use bitsets:
// bitset<N> ok; ok.set(); for each j: ok &= (pos[pat[j]] >> j)  (pos[c] = bitset of positions of c in text)
