// prefix function (kmp). pi[i] = longest proper prefix of s[0..i] that is also a suffix
// find(text, pat) = start positions of every occurrence. period of s = n - pi[n-1] (if it divides n)
vi prefixFunction(const string &s)
{
    int n = s.size();
    vi p(n, 0);
    rep(i, 1, n)
    {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j]) j = p[j - 1];
        if (s[i] == s[j]) j++;
        p[i] = j;
    }
    return p;
}
vi kmpFind(const string &text, const string &pat)
{
    vi res;
    if (pat.empty()) return res;
    vi p = prefixFunction(pat + '\x01' + text); // separator must not appear in the strings
    int m = pat.size();
    rep(i, m + 1, (int)p.size()) if (p[i] == m) res.pb(i - 2 * m);
    return res;
}
// kmp automaton: aut[state][c] for c in 0..25, state = matched length (0..m)
vvi kmpAutomaton(const string &s)
{
    int m = s.size();
    vi p = prefixFunction(s);
    vvi aut(m + 1, vi(26, 0));
    rep(i, 0, m + 1) rep(c, 0, 26)
    {
        if (i < m && s[i] - 'a' == c) aut[i][c] = i + 1;
        else aut[i][c] = i ? aut[p[i - 1]][c] : 0;
    }
    return aut;
}
