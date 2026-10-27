// sparse table for range gcd: O(n log n) build, O(1) query rangeGCD(l, r) on 0-indexed [l, r]
const int MAXN = 200005, MAXLOG = 18; // MAXLOG > log2(MAXN)
int n, q;
int a[MAXN];
int st[MAXN][MAXLOG];

void buildSparseTable() {
    for (int i = 0; i < n; i++)
        st[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            st[i][j] = __gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}

int rangeGCD(int l, int r) {
    int k = log2(r - l + 1);
    return __gcd(st[l][k], st[r - (1 << k) + 1][k]);
}
