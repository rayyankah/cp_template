// double hashing (mod 1e9+7 and 1e9+9). call preCompute(max length) once, then Hash h(s)
// h.getHash(l, r) = hash of s[l..r] (0-based, inclusive), {0, 0} for an empty range
// works for any characters; compare hashes of two strings with the same preCompute
constexpr int MOD1 = 1000000007, MOD2 = 1000000009, p1 = 133, p2 = 137;
vi pow1, pow2;
void preCompute(int n) // do not forget to call it !!
{
    pow1.resize(n + 1), pow2.resize(n + 1);
    pow1[0] = pow2[0] = 1;
    rep(i, 1, n + 1)
    {
        pow1[i] = pow1[i - 1] * p1 % MOD1;
        pow2[i] = pow2[i - 1] * p2 % MOD2;
    }
}
struct Hash
{
    vi hash1, hash2;
    Hash() {}
    Hash(const string &s)
    {
        int n = s.size();
        hash1.assign(n + 1, 0), hash2.assign(n + 1, 0);
        rep(i, 0, n)
        {
            int c = (unsigned char)s[i];
            hash1[i + 1] = (hash1[i] * p1 + c) % MOD1;
            hash2[i + 1] = (hash2[i] * p2 + c) % MOD2;
        }
    }
    pi getHash(int l, int r)
    {
        if (l > r) return {0, 0};
        int len = r - l + 1;
        int h1 = (hash1[r + 1] - hash1[l] * pow1[len] % MOD1 + MOD1) % MOD1;
        int h2 = (hash2[r + 1] - hash2[l] * pow2[len] % MOD2 + MOD2) % MOD2;
        return {h1, h2};
    }
};
