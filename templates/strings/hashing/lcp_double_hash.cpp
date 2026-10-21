// lcp with hashing (needs double_hash.cpp above it, and preCompute(max length) called first)
// works on two different strings or on one string: lcp(ha, i, hb, j) = longest common prefix of a[i..] and b[j..]
// same string: lcp(h, i, h, j). optional lim caps the answer (e.g. compare only up to some length)
// a[i..] < b[j..] in dictionary order: k = lcp(...); then compare a[i + k] and b[j + k] (if one ran out, it is smaller)
int lcp(Hash &ha, int i, Hash &hb, int j, int lim = LLONG_MAX)
{
    int na = (int)ha.hash1.size() - 1, nb = (int)hb.hash1.size() - 1;
    int lo = 0, hi = min({na - i, nb - j, lim});
    while (lo < hi)
    {
        int mid = (lo + hi + 1) / 2;
        if (ha.getHash(i, i + mid - 1) == hb.getHash(j, j + mid - 1)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}
