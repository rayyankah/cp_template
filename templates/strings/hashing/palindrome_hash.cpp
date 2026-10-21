// forward + backward hash (needs double_hash.cpp above it, and preCompute(n) called first)
// PalHash ph(s); ph.fwd(l, r) = hash of s[l..r], ph.bwd(l, r) = hash of s[l..r] read backwards
// ph.isPal(l, r): is s[l..r] a palindrome, O(1). 0-based, inclusive
struct PalHash
{
    int n;
    Hash f, g; // g is built on the reversed string
    PalHash(const string &s) : n(s.size()), f(s), g(string(s.rbegin(), s.rend())) {}
    pi fwd(int l, int r) { return f.getHash(l, r); }
    pi bwd(int l, int r) { return g.getHash(n - 1 - r, n - 1 - l); }
    bool isPal(int l, int r) { return l >= r || fwd(l, r) == bwd(l, r); }
};
