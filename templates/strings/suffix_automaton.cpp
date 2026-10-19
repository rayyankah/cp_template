// suffix automaton of one string. SAM sa(s.size()); for (char c : s) sa.extend(c - 'a');
// every substring = one path from state 0; distinct substrings = sum over v>0 of len[v] - len[link[v]]
// occurrences: call sa.countOcc() -> cnt[v] = how many times the substrings of state v occur
struct SAM
{
    vector<array<int32_t, 26>> nx; // int32 keeps memory low
    vi link, len, cnt;
    int last = 0;
    SAM(int n = 0)
    {
        nx.reserve(2 * n + 2), link.reserve(2 * n + 2), len.reserve(2 * n + 2), cnt.reserve(2 * n + 2);
        newState(0, -1);
    }
    int newState(int l, int lk)
    {
        nx.pb({}), nx.back().fill(-1);
        len.pb(l), link.pb(lk), cnt.pb(0);
        return nx.size() - 1;
    }
    void extend(int c)
    {
        int cur = newState(len[last] + 1, 0), p = last;
        cnt[cur] = 1;
        while (p != -1 && nx[p][c] == -1) nx[p][c] = cur, p = link[p];
        if (p != -1)
        {
            int q = nx[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else
            {
                int cl = newState(len[p] + 1, link[q]);
                nx[cl] = nx[q];
                while (p != -1 && nx[p][c] == q) nx[p][c] = cl, p = link[p];
                link[q] = link[cur] = cl;
            }
        }
        last = cur;
    }
    void countOcc() // push counts up the suffix links, longest states first
    {
        int n = len.size();
        vi order(n);
        iota(all(order), 0);
        sort(all(order), [&](int a, int b) { return len[a] > len[b]; });
        for (int v : order) if (link[v] >= 0) cnt[link[v]] += cnt[v];
    }
    int distinctSubstrings()
    {
        int res = 0;
        rep(v, 1, (int)len.size()) res += len[v] - len[link[v]];
        return res;
    }
};
