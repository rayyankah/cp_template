// non-negative big integers as decimal strings (most significant digit first)
// bigAdd, bigSub (a >= b), bigMulSmall (by an int up to ~1e17), bigMul (O(n*m)), bigCmp, bigDivSmall
int bigCmp(const string &a, const string &b)
{
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    return a < b ? -1 : (a > b ? 1 : 0);
}
string strip(string s)
{
    int i = 0;
    while (i + 1 < (int)s.size() && s[i] == '0') i++;
    return s.substr(i);
}
string bigAdd(const string &a, const string &b)
{
    string r;
    int i = a.size() - 1, j = b.size() - 1, c = 0;
    while (i >= 0 || j >= 0 || c)
    {
        int d = c + (i >= 0 ? a[i--] - '0' : 0) + (j >= 0 ? b[j--] - '0' : 0);
        r += char('0' + d % 10), c = d / 10;
    }
    reverse(all(r));
    return r;
}
string bigSub(const string &a, const string &b)
{
    string r;
    int i = a.size() - 1, j = b.size() - 1, c = 0;
    while (i >= 0)
    {
        int d = a[i--] - '0' - c - (j >= 0 ? b[j--] - '0' : 0);
        c = d < 0, r += char('0' + (d + 10) % 10);
    }
    reverse(all(r));
    return strip(r);
}
string bigMulSmall(const string &a, int k)
{
    if (k == 0) return "0";
    string r;
    __int128 c = 0;
    repb(i, (int)a.size() - 1, 0)
    {
        c += (__int128)(a[i] - '0') * k;
        r += char('0' + (int)(c % 10)), c /= 10;
    }
    while (c) r += char('0' + (int)(c % 10)), c /= 10;
    reverse(all(r));
    return strip(r);
}
string bigMul(const string &a, const string &b)
{
    vi d(a.size() + b.size(), 0);
    repb(i, (int)a.size() - 1, 0) repb(j, (int)b.size() - 1, 0) d[i + j + 1] += (a[i] - '0') * (b[j] - '0');
    repb(i, (int)d.size() - 1, 1) d[i - 1] += d[i] / 10, d[i] %= 10;
    string r;
    for (int x : d) r += char('0' + x);
    return strip(r);
}
string bigDivSmall(const string &a, int k, int &rem) // quotient, remainder in rem
{
    string q;
    rem = 0;
    for (char c : a)
    {
        rem = rem * 10 + (c - '0');
        q += char('0' + rem / k), rem %= k;
    }
    return strip(q);
}
