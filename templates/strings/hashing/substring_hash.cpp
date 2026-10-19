// single-mod substring hash, O(n) build, O(1) query. for safety prefer double_hash.cpp
// SingleHash h(s); h.get(l, r) = hash of s[l..r] (0-based, inclusive)
struct SingleHash
{
    static const int M = 1000000007, B = 131;
    vi h, pw;
    SingleHash(const string &s)
    {
        int n = s.size();
        h.assign(n + 1, 0), pw.assign(n + 1, 1);
        rep(i, 0, n)
        {
            h[i + 1] = (h[i] * B + (unsigned char)s[i]) % M;
            pw[i + 1] = pw[i] * B % M;
        }
    }
    int get(int l, int r) { return (h[r + 1] - h[l] * pw[r - l + 1] % M + M) % M; }
};
