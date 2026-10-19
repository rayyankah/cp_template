// chinese remainder theorem for any moduli (not necessarily coprime)
// crt({r1, m1}, {r2, m2}, ...) -> {r, lcm} or {-1, -1} if no solution. needs extgcd (base template)
pi crtMerge(int r1, int m1, int r2, int m2)
{
    int x, y, g = extgcd(m1, m2, x, y);
    if ((r2 - r1) % g != 0) return {-1, -1};
    int l = m1 / g * m2;
    int k = (__int128)((r2 - r1) / g) * x % (m2 / g);
    int r = ((r1 + (__int128)m1 * k) % l + l) % l;
    return {r, l};
}
pi crt(const vpi &eqs) // eqs[i] = {remainder, modulus}
{
    pi cur = {0, 1};
    for (auto &e : eqs)
    {
        cur = crtMerge(cur.first, cur.second, ((e.first % e.second) + e.second) % e.second, e.second);
        if (cur.first == -1) return cur;
    }
    return cur;
}
// inverse of a mod m for any m (gcd(a, m) must be 1), -1 otherwise
int invGeneral(int a, int m)
{
    int x, y, g = extgcd(((a % m) + m) % m, m, x, y);
    if (g != 1) return -1;
    return ((x % m) + m) % m;
}
