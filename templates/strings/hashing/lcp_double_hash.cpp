// double polynomial hash with substring hash and lcp of two suffixes by binary search
// build(s); get(l, len); lcp(i, j, n)
const int m1 = 1e9 + 7, m2 = 998244353, base = 131;
vi h1, h2, p1, p2;
void build(string &s)
{
    int n = s.size();
    h1.assign(n + 1, 0), h2.assign(n + 1, 0), p1.assign(n + 1, 1), p2.assign(n + 1, 1);
    rep(i, 0, n)
    {
        h1[i + 1] = (h1[i] * base + s[i]) % m1, h2[i + 1] = (h2[i] * base + s[i]) % m2;
        p1[i + 1] = p1[i] * base % m1, p2[i + 1] = p2[i] * base % m2;
    }
}
pi get(int l, int len) // hash of s[l .. l+len-1]
{
    return {((h1[l + len] - h1[l] * p1[len]) % m1 + m1) % m1, ((h2[l + len] - h2[l] * p2[len]) % m2 + m2) % m2};
}
int lcp(int i, int j, int n) // longest common prefix of suffixes i and j
{
    int lo = 0, hi = n - max(i, j);
    while (lo < hi)
    {
        int mid = (lo + hi + 1) / 2;
        if (get(i, mid) == get(j, mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}
