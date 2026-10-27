// xor basis (linear basis over GF(2)) for numbers < 2^B
// insert(x): true if x was independent. canMake(x): is x a xor of some subset. maxXor(): best subset xor
// number of distinct subset xors = 2^rank. k-th smallest subset xor: reduce the basis, then use bits of k
struct XorBasis
{
    static const int B = 61;
    int b[B] = {0}, rank = 0;
    bool insert(int x)
    {
        repb(i, B - 1, 0) if (x >> i & 1)
        {
            if (!b[i]) { b[i] = x, rank++; return true; }
            x ^= b[i];
        }
        return false;
    }
    bool canMake(int x) { repb(i, B - 1, 0) if (x >> i & 1) { if (!b[i]) return false; x ^= b[i]; } return true; }
    int maxXor(int x = 0) { repb(i, B - 1, 0) x = max(x, x ^ b[i]); return x; } // max of x ^ (subset xor)
    int minXor(int x) { repb(i, B - 1, 0) x = min(x, x ^ b[i]); return x; }
    int kth(int k) // k-th smallest (0-based) among the 2^rank distinct subset xors (0 included), k < 2^rank
    {
        vi v;
        repb(i, B - 1, 0) if (b[i]) rep(j, i + 1, B) if (b[j] >> i & 1) b[j] ^= b[i]; // reduce
        rep(i, 0, B) if (b[i]) v.pb(b[i]);
        int r = 0;
        rep(i, 0, (int)v.size()) if (k >> i & 1) r ^= v[i];
        return r;
    }
};
