// burrows-wheeler transform. bwt(s): s must end with a unique smallest char (e.g. '#' or '$')
// last column of the sorted rotations. inverseBwt(t): give back s (with the marker at the end)
string bwt(const string &s)
{
    int n = s.size();
    vi r(n);
    iota(all(r), 0);
    string d = s + s;
    sort(all(r), [&](int a, int b) { return d.compare(a, n, d, b, n) < 0; }); // O(n^2 log n): use SuffixArray for big n
    string t;
    for (int i : r) t += s[(i + n - 1) % n];
    return t;
}
string inverseBwt(const string &t, char marker = '#')
{
    int n = t.size();
    vi idx(n);
    iota(all(idx), 0);
    stable_sort(all(idx), [&](int a, int b) { return t[a] < t[b]; }); // idx[i] = row of last column feeding sorted row i
    int row = find(all(t), marker) - t.begin();
    string s;
    rep(k, 0, n) row = idx[row], s += t[row];
    return s;
}
