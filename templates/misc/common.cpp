// small everyday helpers

// coordinate compression: vals sorted unique, idx = lower_bound position
vi compress(vi &a) // replaces a[i] by its rank (0-based), returns the sorted unique values
{
    vi v = a;
    sort(all(v)), v.erase(unique(all(v)), v.end());
    for (int &x : a) x = lower_bound(all(v), x) - v.begin();
    return v;
}

// longest strictly increasing subsequence in O(n log n). for non-decreasing use upper_bound
int lis(const vi &a)
{
    vi d;
    for (int x : a)
    {
        auto it = lower_bound(all(d), x);
        if (it == d.end()) d.pb(x); else *it = x;
    }
    return d.size();
}

// binary search on the answer: smallest x in [lo, hi] with ok(x) true (ok is monotone false...true), hi + 1 if none
template <class F> int firstTrue(int lo, int hi, F ok)
{
    hi++;
    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (ok(mid)) hi = mid; else lo = mid + 1;
    }
    return lo;
}

// ternary search for the max of a unimodal function on integers [lo, hi]
template <class F> int ternaryMax(int lo, int hi, F f)
{
    while (hi - lo > 2)
    {
        int m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) lo = m1; else hi = m2;
    }
    int best = lo;
    rep(x, lo, hi + 1) if (f(x) > f(best)) best = x;
    return best;
}
// on doubles: repeat 100 times with m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3

// bit tricks
// for (int s = mask; s; s = (s - 1) & mask)  -> every non-empty submask of mask (3^n total over all masks)
// __builtin_popcountll(x), __builtin_ctzll(x) (lowest set bit index), 63 - __builtin_clzll(x) (highest)
// sum over subsets (SOS dp): f[mask] = sum of a[sub] over all sub of mask, O(n 2^n)
void sosSubsets(vi &f, int n)
{
    rep(i, 0, n) rep(mask, 0, 1LL << n) if (mask >> i & 1) f[mask] += f[mask ^ (1LL << i)];
}
void sosSupersets(vi &f, int n) // f[mask] = sum over supersets
{
    rep(i, 0, n) rep(mask, 0, 1LL << n) if (!(mask >> i & 1)) f[mask] += f[mask | (1LL << i)];
}

// prefix sums 2d: P[i+1][j+1] = a[i][j] + P[i][j+1] + P[i+1][j] - P[i][j]
// rectangle (r1, c1)..(r2, c2) = P[r2+1][c2+1] - P[r1][c2+1] - P[r2+1][c1] + P[r1][c1]

// __int128 input / output
__int128 read128()
{
    string s;
    cin >> s;
    __int128 x = 0;
    bool neg = s[0] == '-';
    for (char c : s) if (isdigit(c)) x = x * 10 + (c - '0');
    return neg ? -x : x;
}
string str128(__int128 x)
{
    if (x == 0) return "0";
    bool neg = x < 0;
    string s;
    while (x) s += char('0' + (neg ? -(x % 10) : x % 10)), x /= 10;
    if (neg) s += '-';
    reverse(all(s));
    return s;
}
