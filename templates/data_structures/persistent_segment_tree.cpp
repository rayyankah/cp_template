// persistent segment tree over values [0, V): version k = first k elements inserted
// kth smallest in a[l..r]: build roots by inserting compressed values, then kth(root[r+1], root[l], k)
struct PST
{
    vi L, R, cnt;
    int V;
    PST(int V, int reserveNodes = 0) : V(V) { L.reserve(reserveNodes), R.reserve(reserveNodes), cnt.reserve(reserveNodes); L.pb(0), R.pb(0), cnt.pb(0); } // node 0 = empty
    int insert(int prev, int pos, int l = 0, int r = -1)
    {
        if (r == -1) r = V - 1;
        int v = L.size();
        L.pb(L[prev]), R.pb(R[prev]), cnt.pb(cnt[prev] + 1);
        if (l == r) return v;
        int m = (l + r) / 2;
        if (pos <= m) { int c = insert(L[prev], pos, l, m); L[v] = c; }
        else { int c = insert(R[prev], pos, m + 1, r); R[v] = c; }
        return v;
    }
    int kth(int hiRoot, int loRoot, int k, int l = 0, int r = -1) // k is 1-based, returns compressed value
    {
        if (r == -1) r = V - 1;
        while (l < r)
        {
            int m = (l + r) / 2, left = cnt[L[hiRoot]] - cnt[L[loRoot]];
            if (k <= left) hiRoot = L[hiRoot], loRoot = L[loRoot], r = m;
            else k -= left, hiRoot = R[hiRoot], loRoot = R[loRoot], l = m + 1;
        }
        return l;
    }
};
