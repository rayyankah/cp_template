// generalized suffix automaton: for every string set s.last = 0, then s.ins(c) for each char (c in 0..25)
// ins returns the state of the current prefix; len / link / nx as usual
struct sam
{
    vector<array<int32_t, 26>> nx;
    vector<int32_t> link, len;
    int last = 0;
    sam(int cap)
    {
        nx.reserve(cap), link.reserve(cap), len.reserve(cap);
        add(0, -1);
    }
    int add(int l, int lk)
    {
        array<int32_t, 26> e;
        e.fill(-1);
        nx.pb(e), len.pb(l), link.pb(lk);
        return len.size() - 1;
    }
    int ins(int c) // returns the state of the new prefix
    {
        int p = last;
        if (nx[p][c] >= 0) // the prefix already exists (generalized case)
        {
            int q = nx[p][c];
            if (len[p] + 1 == len[q]) return last = q;
            int cl = add(len[p] + 1, link[q]);
            nx[cl] = nx[q];
            while (p >= 0 && nx[p][c] == q) nx[p][c] = cl, p = link[p];
            link[q] = cl;
            return last = cl;
        }
        int cur = add(len[last] + 1, 0);
        while (p >= 0 && nx[p][c] < 0) nx[p][c] = cur, p = link[p];
        if (p >= 0)
        {
            int q = nx[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else
            {
                int cl = add(len[p] + 1, link[q]);
                nx[cl] = nx[q];
                while (p >= 0 && nx[p][c] == q) nx[p][c] = cl, p = link[p];
                link[q] = cl, link[cur] = cl;
            }
        }
        return last = cur;
    }
};
