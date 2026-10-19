// 2D hash: hash rows with base b1, then the column of row hashes with base b2 (one modulus 2^61-1)
// Hash2D h(grid); h.get(r1, c1, r2, c2) = hash of the sub-rectangle (0-based, inclusive)
// equal rectangles of the same size give equal hashes; compare only same-size rectangles
struct Hash2D
{
    typedef unsigned long long ull;
    static const ull M = (1ULL << 61) - 1;
    static ull mul(ull a, ull b) { __int128 r = (__int128)a * b; ull x = (ull)(r & M) + (ull)(r >> 61); return x >= M ? x - M : x; }
    ull b1 = 131, b2 = 1000003;
    int n, m;
    vector<vector<ull>> h;
    vector<ull> p1, p2;
    Hash2D(const vector<string> &g)
    {
        n = g.size(), m = g[0].size();
        p1.assign(m + 1, 1), p2.assign(n + 1, 1);
        rep(i, 1, m + 1) p1[i] = mul(p1[i - 1], b1);
        rep(i, 1, n + 1) p2[i] = mul(p2[i - 1], b2);
        h.assign(n + 1, vector<ull>(m + 1, 0));
        rep(i, 0, n) rep(j, 0, m)
        {
            ull v = mul(h[i + 1][j], b1) + (unsigned char)g[i][j];
            h[i + 1][j + 1] = v % M;
        }
        rep(i, 0, n) rep(j, 0, m + 1) h[i + 1][j] = (h[i + 1][j] + mul(h[i][j], b2)) % M;
    }
    ull sub(ull a, ull b) { return a >= b ? a - b : a + M - b; }
    ull get(int r1, int c1, int r2, int c2)
    {
        r2++, c2++;
        int w = c2 - c1, ht = r2 - r1;
        ull A = sub(h[r2][c2], mul(h[r2][c1], p1[w]));
        ull B = sub(h[r1][c2], mul(h[r1][c1], p1[w]));
        return sub(A, mul(B, p2[ht]));
    }
};
