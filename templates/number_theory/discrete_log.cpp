// discrete log (baby step giant step): smallest x >= 0 with a^x = b (mod m), any m, -1 if none. O(sqrt m)
int discreteLog(int a, int b, int m)
{
    a %= m, b %= m;
    int k = 1 % m, add = 0, g;
    while ((g = __gcd(a, m)) > 1) // make a and m coprime
    {
        if (b == k) return add;
        if (b % g) return -1;
        b /= g, m /= g, add++;
        k = k * (a / g) % m;
    }
    int n = sqrtl((long double)m) + 1, an = 1;
    rep(i, 0, n) an = an * a % m;
    unordered_map<int, int> vals;
    for (int q = 0, cur = b; q <= n; q++) vals[cur] = q, cur = cur * a % m;
    for (int p = 1, cur = k; p <= n; p++)
    {
        cur = cur * an % m;
        if (vals.count(cur)) return n * p - vals[cur] + add;
    }
    return -1;
}
