//================ Code starts here ================
void solve()
{
    string str;
    cin >> str;
    string gb;
    cin >> gb;
    int k;
    cin >> k;
    int n = (int)str.size();

    vi good(n, 1);
    rep(i, 0, n)
    {
        if (gb[str[i] - 'a'] == '1')
        {
            good[i] = 0;
        }
    }
    vi pref_bad = good;
    rep(i, 1, n)
    {
        pref_bad[i] += pref_bad[i - 1];
    }

    // prepare both hashes
    compute_pref_hash(str);

    // store pair(mod_hash, ull_hash)
    unordered_set<pair<ll, unsigned long long>, pair_hash> s;
    long long est = 1LL * n * (n + 1) / 2;
    if (est > 1000000) est = 1000000;
    s.reserve((size_t)est);

    rep(i, 0, n)
    {
        rep(j, i, n)
        {
            int r = j;
            int diff = pref_bad[r];
            if (i > 0)
            {
                diff -= pref_bad[i - 1];
            }
            if (diff > k)
            {
                break;
            }
            ll h1 = substringHash(i, j);
            unsigned long long h2 = substringHash2(i, j);
            s.insert({h1, h2});
        }
    }

    cout << s.size() << nl;
}

signed main()
{
    fast;
    int t = 1;
    while (t--)
    {
        solve();
    }
}
