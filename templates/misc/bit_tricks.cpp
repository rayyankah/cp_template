// bit identities:  a + b = (a ^ b) + 2 (a & b)      a + b = (a | b) + (a & b)      a ^ b = (a | b) - (a & b)
// min over d of (a ^ d) + (b ^ d) = a ^ b              popcount: __builtin_popcountll(x)
// highest bit: 63 - __builtin_clzll(x) (x > 0)        lowest set bit: x & -x      trailing zeros: __builtin_ctzll(x)
// subsets of mask: for (int s = mask; s > 0; s = (s - 1) & mask)   (add s = 0 separately)
// OR / AND of a growing subarray changes at most ~60 times -> keep the list of distinct values ending at i

// max over i, j of (a[i] & b[j]) in O((n + m) * B): greedy from the high bit, keep only candidates having all chosen bits
int maxAndPair(vi a, vi b, int B = 30)
{
    int ans = 0;
    repb(bit, B - 1, 0)
    {
        int want = ans | (1LL << bit);
        vi na, nb;
        for (int x : a) if ((x & want) == want) na.pb(x);
        for (int x : b) if ((x & want) == want) nb.pb(x);
        if (!na.empty() && !nb.empty()) ans = want, a = na, b = nb;
    }
    return ans;
}
// max (a[i] & a[j]) with i != j inside ONE array: same idea, need at least 2 candidates
int maxAndPairOne(vi a, int B = 30)
{
    int ans = 0;
    repb(bit, B - 1, 0)
    {
        int want = ans | (1LL << bit);
        vi na;
        for (int x : a) if ((x & want) == want) na.pb(x);
        if (na.size() >= 2) ans = want, a = na;
    }
    return ans;
}
// max xor pair: insert into BinTrie (binary_trie.cpp), answer max over x of t.maxXor(x) before inserting x
// sum over all pairs i < j of (a[i] ^ a[j]): per bit, ones * zeros * 2^bit
int sumPairXor(const vi &a, int B = 31)
{
    int n = a.size(), s = 0;
    rep(bit, 0, B) { int c = 0; for (int x : a) c += x >> bit & 1; s += c * (n - c) * (1LL << bit); }
    return s;
}
// SOS dp (sum over subsets / supersets): sosSubsets, sosSupersets in misc/common.cpp
