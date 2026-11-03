// dp optimizations: divide & conquer, Knuth, monotone convex hull trick, slope trick
// (Li Chao tree for unsorted lines/queries: data_structures/li_chao.cpp)

// ---------- divide & conquer optimization ----------
// dp[j][i] = min over p < i of dp[j-1][p] + cost(p+1, i), when the best p (opt) is non-decreasing in i
// O(k n log n) * (cost of costOf). set prv[0] = 0, prv[i>0] = INF for the first layer, run k layers
namespace DnC
{
    const int INF = LLONG_MAX / 4;
    vi prv, cur;
    function<int(int, int)> costOf;        // cost of the piece l..r (1-indexed, inclusive)
    void compute(int lo, int hi, int optl, int optr)
    {
        if (lo > hi) return;
        int mid = (lo + hi) / 2, best = INF, bj = optl;
        for (int p = optl; p <= min(mid - 1, optr); p++)
        {
            if (prv[p] >= INF) continue;
            int c = prv[p] + costOf(p + 1, mid);
            if (c < best) best = c, bj = p;
        }
        cur[mid] = best;
        compute(lo, mid - 1, optl, bj);
        compute(mid + 1, hi, bj, optr);
    }
    int solve(int n, int k)                // cut 1..n into exactly k non-empty pieces
    {
        prv.assign(n + 1, INF);
        prv[0] = 0;
        rep(layer, 0, k)
        {
            cur.assign(n + 1, INF);
            compute(1, n, 0, n - 1);
            prv = cur;
        }
        return prv[n];
    }
}
// moving-window cost (Mo style), e.g. number of equal pairs inside a[l..r]: keep cl, cr, cnt[], cost
// and move the window inside costOf; total movement is O(n log n) per layer

// ---------- Knuth optimization ----------
// dp[i][j] = min over i < k < j of dp[i][k] + dp[k][j] + w(i, j), dp[i][i+1] = 0
// valid when opt[i][j-1] <= opt[i][j] <= opt[i+1][j] (w satisfies the quadrangle inequality). O(n^2)
// example: breaking a string at points p[0] = 0 < p[1] < ... < p[m+1] = len, w(i, j) = p[j] - p[i]
int knuth(const vi &p)
{
    int K = p.size();
    vvi dp(K, vi(K, 0)), opt(K, vi(K, 0));
    rep(i, 0, K - 1) opt[i][i + 1] = i + 1;
    rep(len, 2, K) rep(i, 0, K - len)
    {
        int j = i + len, best = LLONG_MAX, bk = i + 1;
        for (int k = max(i + 1, opt[i][j - 1]); k <= min(j - 1, opt[i + 1][j]); k++)
            if (dp[i][k] + dp[k][j] < best) best = dp[i][k] + dp[k][j], bk = k;
        dp[i][j] = best + p[j] - p[i];
        opt[i][j] = bk;
    }
    return dp[0][K - 1];
}

// ---------- monotone convex hull trick (minimum) ----------
// add lines in order of DECREASING slope, query x in INCREASING order: amortized O(1)
// for maximum: add (-m, -b) and negate the answer. unsorted -> Li Chao
struct MonoCHT
{
    deque<pair<int, int>> h;               // (slope, intercept)
    static int val(const pair<int, int> &l, int x) { return l.first * x + l.second; }
    static bool bad(const pair<int, int> &a, const pair<int, int> &b, const pair<int, int> &c)
    {
        return (__int128)(c.second - a.second) * (a.first - b.first) <= (__int128)(b.second - a.second) * (a.first - c.first);
    }
    void add(int m, int b)
    {
        if (!h.empty() && h.back().first == m)
        {
            if (h.back().second <= b) return;
            h.pop_back();
        }
        pair<int, int> l = {m, b};
        while (h.size() >= 2 && bad(h[h.size() - 2], h.back(), l)) h.pop_back();
        h.push_back(l);
    }
    int query(int x)
    {
        while (h.size() >= 2 && val(h[0], x) >= val(h[1], x)) h.pop_front();
        return val(h[0], x);
    }
};

// ---------- slope trick ----------
// min total |change| to make a non-decreasing (strictly increasing: use a[i] - i)
int makeNonDecreasing(const vi &a)
{
    priority_queue<int> pq;
    int ans = 0;
    for (int x : a)
    {
        pq.push(x);
        if (pq.top() > x) ans += pq.top() - x, pq.pop(), pq.push(x);
    }
    return ans;
}
