// interval assignment ("chtholly tree" / ODT): the array is kept as runs [l, r] of equal value in a map
// assign(l, r, v) merges [l, r] into one run. with random queries / mostly assigns it stays small.
// guaranteed fast if every operation that walks runs is an assign on the same range (runs only drop)
// ODT t(n, init); t.assign(l, r, v); t.sum(l, r); for any other query walk split(l)..split(r+1)
struct ODT
{
    map<int, int> mp; // run start -> value, runs cover [0, n)
    int n;
    ODT(int n, int init = 0) : n(n) { mp[0] = init, mp[n] = 0; } // sentinel at n
    map<int, int>::iterator split(int pos) // make pos the start of a run, return it
    {
        auto it = mp.lower_bound(pos);
        if (it != mp.end() && it->first == pos) return it;
        --it;
        return mp.insert({pos, it->second}).first;
    }
    void assign(int l, int r, int v) // 0-based inclusive
    {
        auto itr = split(r + 1), itl = split(l);
        mp.erase(itl, itr);
        mp[l] = v;
    }
    int sum(int l, int r)
    {
        auto itr = split(r + 1), itl = split(l);
        int s = 0;
        for (auto it = itl; it != itr; ++it) s += it->second * (next(it)->first - it->first);
        return s;
    }
    int runs(int l, int r) { auto itr = split(r + 1), itl = split(l); return distance(itl, itr); } // runs inside
};
