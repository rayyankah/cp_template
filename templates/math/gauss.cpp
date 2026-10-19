// gaussian elimination mod a prime p: solve A x = b. returns 0 (no solution), 1 (unique), 2 (infinitely many)
// x gets one solution. needs binExp
int gaussMod(vector<vi> a, vi b, vi &x, int p = MOD)
{
    int n = a.size(), m = a[0].size();
    rep(i, 0, n) a[i].pb(b[i]);
    vi where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; col++)
    {
        int sel = -1;
        rep(i, row, n) if (a[i][col]) { sel = i; break; }
        if (sel == -1) continue;
        swap(a[sel], a[row]);
        where[col] = row;
        int inv = binExp(a[row][col], p - 2, p);
        rep(j, 0, m + 1) a[row][j] = a[row][j] * inv % p;
        rep(i, 0, n) if (i != row && a[i][col])
        {
            int f = a[i][col];
            rep(j, 0, m + 1) a[i][j] = ((a[i][j] - f * a[row][j]) % p + p) % p;
        }
        row++;
    }
    x.assign(m, 0);
    rep(j, 0, m) if (where[j] != -1) x[j] = a[where[j]][m];
    rep(i, 0, n)
    {
        int s = 0;
        rep(j, 0, m) s = (s + a[i][j] * x[j]) % p;
        if (s != a[i][m]) return 0;
    }
    rep(j, 0, m) if (where[j] == -1) return 2;
    return 1;
}
// gaussian elimination with doubles: same idea, pick the largest pivot (partial pivoting), EPS = 1e-9
// xor basis (linear algebra over bits): insert numbers, max xor of a subset, check representability
struct XorBasis
{
    int b[63] = {0}, rnk = 0;
    bool insert(int x)
    {
        repb(i, 62, 0) if (x >> i & 1)
        {
            if (!b[i]) { b[i] = x, rnk++; return true; }
            x ^= b[i];
        }
        return false; // x was already representable
    }
    bool canMake(int x) { repb(i, 62, 0) if (x >> i & 1) { if (!b[i]) return false; x ^= b[i]; } return true; }
    int maxXor(int x = 0) { repb(i, 62, 0) x = max(x, x ^ b[i]); return x; }
};
