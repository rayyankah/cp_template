// exact fraction p/q, always reduced, q > 0. __int128 inside so products of 1e18-size values don't overflow
// Frac a(3, 4), b(1, 6); a + b, a - b, a * b, a / b, a < b, a == b; cout << a  prints "p/q"
// for "p/q" output also when q = 1, keep print as is; if the judge wants just "p" when q = 1, change print
struct Frac
{
    __int128 p, q;
    static __int128 g(__int128 a, __int128 b) { if (a < 0) a = -a; if (b < 0) b = -b; while (b) { __int128 t = a % b; a = b, b = t; } return a; }
    Frac(__int128 a = 0, __int128 b = 1)
    {
        if (b < 0) a = -a, b = -b;
        __int128 d = g(a, b);
        if (d == 0) d = 1;
        p = a / d, q = b / d;
    }
    Frac operator+(const Frac &o) const { return Frac(p * o.q + o.p * q, q * o.q); }
    Frac operator-(const Frac &o) const { return Frac(p * o.q - o.p * q, q * o.q); }
    Frac operator*(const Frac &o) const { return Frac(p * o.p, q * o.q); }
    Frac operator/(const Frac &o) const { return Frac(p * o.q, q * o.p); } // o must not be 0
    bool operator<(const Frac &o) const { return p * o.q < o.p * q; }
    bool operator==(const Frac &o) const { return p == o.p && q == o.q; }
    long double val() const { return (long double)p / (long double)q; }
    int modval(int m = MOD) const { return (int)(((p % m) + m) % m) * binExp((int)(q % m), m - 2, m) % m; } // p * q^-1 mod prime m
};
string i128(__int128 x) { if (x == 0) return "0"; bool neg = x < 0; if (neg) x = -x; string s; while (x) s += char('0' + x % 10), x /= 10; if (neg) s += '-'; reverse(all(s)); return s; }
ostream &operator<<(ostream &os, const Frac &f) { return os << i128(f.p) << "/" << i128(f.q); }
