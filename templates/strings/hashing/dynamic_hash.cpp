// hashing with point updates: change a character, compare / test palindrome on any range in O(log n)
// DynHash h(s); h.set(i, c); h.get(l, r) = hash of s[l..r]; with a reversed copy you can test palindromes
// stores c * B^i in a fenwick tree, then normalises by multiplying with B^(n - 1 - r) instead of dividing
struct DynHash
{
    static const int M1 = 1000000007, M2 = 1000000009, B = 131;
    int n;
    vi t1, t2, pw1, pw2, val;
    DynHash(const string &s) : n(s.size()), t1(n + 1, 0), t2(n + 1, 0), pw1(n + 1, 1), pw2(n + 1, 1), val(n, 0)
    {
        rep(i, 1, n + 1) pw1[i] = pw1[i - 1] * B % M1, pw2[i] = pw2[i - 1] * B % M2;
        rep(i, 0, n) set(i, (unsigned char)s[i]);
    }
    void add(vi &t, int i, int v, int M) { for (i++; i <= n; i += i & -i) t[i] = (t[i] + v) % M; }
    int pre(vi &t, int i, int M) { int s = 0; for (i++; i > 0; i -= i & -i) s = (s + t[i]) % M; return s; }
    void set(int i, int c) // s[i] = c
    {
        int d = c - val[i];
        val[i] = c;
        add(t1, i, ((d % M1 + M1) % M1) * pw1[i] % M1, M1);
        add(t2, i, ((d % M2 + M2) % M2) * pw2[i] % M2, M2);
    }
    pi get(int l, int r) // comparable between equal-length ranges of the same or another DynHash of the same n
    {
        int a = (pre(t1, r, M1) - (l ? pre(t1, l - 1, M1) : 0) + M1) % M1;
        int b = (pre(t2, r, M2) - (l ? pre(t2, l - 1, M2) : 0) + M2) % M2;
        return {a * pw1[n - 1 - r] % M1, b * pw2[n - 1 - r] % M2}; // shift so the range ends at n - 1
    }
};
// palindrome check on s[l..r] with updates: keep DynHash f(s) and g(reversed s);
// s[l..r] is a palindrome  <=>  f.get(l, r) == g.get(n - 1 - r, n - 1 - l)
// careful: get() aligns ranges to the right end, so compare ranges with the same r-alignment as above (same length works)
