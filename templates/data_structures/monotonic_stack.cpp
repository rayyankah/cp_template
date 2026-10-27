// previous / next smaller element with a stack, O(n). -1 / n when none
// prevLess[i] = last j < i with a[j] < a[i];  nextLessEq[i] = first j > i with a[j] <= a[i]
// (strict on one side, non-strict on the other, so equal values are counted exactly once)
void prevNext(const vi &a, vi &pl, vi &nl_)
{
    int n = a.size();
    pl.assign(n, -1), nl_.assign(n, n);
    vi st;
    rep(i, 0, n)
    {
        while (!st.empty() && a[st.back()] >= a[i]) nl_[st.back()] = i, st.pop_back();
        pl[i] = st.empty() ? -1 : st.back();
        st.pb(i);
    }
}
// sum over all subarrays of min(subarray): a[i] is the min of (i - pl[i]) * (nl[i] - i) subarrays
int sumSubarrayMin(const vi &a)
{
    vi pl, nx;
    prevNext(a, pl, nx);
    int s = 0;
    rep(i, 0, (int)a.size()) s += a[i] * (i - pl[i]) * (nx[i] - i); // use % MOD if it can overflow
    return s;
}
// sum of max: negate the array, take sumSubarrayMin, negate back
int sumSubarrayMax(vi a) { for (int &x : a) x = -x; return -sumSubarrayMin(a); }
// largest rectangle in a histogram: for each bar, width = nextLess - prevLess - 1 (use strict on both sides
// or the version above: it still gives the right maximum)
int largestRectangle(const vi &h)
{
    vi pl, nx;
    prevNext(h, pl, nx);
    int best = 0;
    rep(i, 0, (int)h.size()) best = max(best, h[i] * (nx[i] - pl[i] - 1));
    return best;
}
// sliding window minimum (window k): deque of indices with increasing values
vi slidingMin(const vi &a, int k)
{
    deque<int> dq;
    vi res;
    rep(i, 0, (int)a.size())
    {
        while (!dq.empty() && a[dq.back()] >= a[i]) dq.pop_back();
        dq.pb(i);
        if (dq.front() <= i - k) dq.pop_front();
        if (i >= k - 1) res.pb(a[dq.front()]);
    }
    return res;
}
