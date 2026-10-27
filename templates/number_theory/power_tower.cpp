// (1) a^e mod m when e is a HUGE decimal string (10^4+ digits):
//     m prime and gcd(a, m) = 1: reduce e mod (m - 1) (fermat).  any m: use powStrGeneral (generalised euler)
// (2) generalised euler: for any a, m and e >= log2(m):  a^e = a^(e mod phi(m) + phi(m))  (mod m)
// (3) power tower a1^(a2^(a3^...)) mod m by recursion m -> phi(m) -> phi(phi(m)) -> ... (depth O(log m))
int phiSqrt(int m) { int r = m; for (int p = 2; p * p <= m; p++) if (m % p == 0) { while (m % p == 0) m /= p; r -= r / p; } if (m > 1) r -= r / m; return r; }
int powStrPrime(int a, const string &e, int m) // m prime, a % m != 0
{
    int r = 0;
    for (char c : e) r = (r * 10 + (c - '0')) % (m - 1);
    return binExp(a % m, r, m);
}
int powStrGeneral(int a, const string &e, int m) // any a, any m >= 1
{
    int ph = phiSqrt(m), r = 0;
    bool big = false; // is e >= ph ?
    for (char c : e) { r = r * 10 + (c - '0'); if (r >= ph) big = true, r %= ph; }
    return binExp(a % m, big ? r + ph : r, m) % m;
}
// tower: a[0]^(a[1]^(a[2]^...)) mod m, any m >= 1, any a[i] >= 0 (0^0 = 1). O(len * sqrt(m)) for phi
const int CAPV = (int)4e18;
int powCap(int a, int e) // min(a^e, CAPV), exact below CAPV
{
    if (a == 0) return e == 0 ? 1 : 0;
    if (a == 1 || e == 0) return 1;
    __int128 v = 1;
    rep(i, 0, e) { v *= a; if (v >= CAPV) return CAPV; }
    return (int)v;
}
int towerRec(const vi &a, const vi &capv, int i, int m)
{
    if (m == 1) return 0;
    if (i == (int)a.size() - 1) return a[i] % m;
    int E = capv[i + 1], ph = phiSqrt(m);
    int ex = (E >= ph) ? towerRec(a, capv, i + 1, ph) + ph : E; // generalised euler when the exponent is big
    return binExp(a[i] % m, ex, m) % m;
}
int tower(const vi &a, int m)
{
    int n = a.size();
    vi capv(n);
    capv[n - 1] = min(a[n - 1], CAPV);
    repb(i, n - 2, 0) capv[i] = powCap(a[i], capv[i + 1]);
    return towerRec(a, capv, 0, m);
}
