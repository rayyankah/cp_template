// de bruijn sequence over m symbols, windows of length n (fkm algorithm)
// set n, m, need, a.assign(n + 1, 0), call db(1, 1); seq has the cyclic sequence (stops after need symbols)
// de bruijn sequence (fkm algorithm), stops early once 'need' symbols are generated
int n, m, need;
vi a, seq;
void db(int t, int p)
{
    if ((int)seq.size() >= need) return;
    if (t > n)
    {
        if (n % p == 0) rep(j, 1, p + 1) seq.pb(a[j]);
        return;
    }
    a[t] = a[t - p];
    db(t + 1, p);
    rep(j, a[t - p] + 1, m)
    {
        a[t] = j;
        db(t + 1, t);
    }
}
