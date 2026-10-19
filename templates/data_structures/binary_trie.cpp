// binary trie on numbers < 2^30: insert / erase (multiset) / max xor with x / min xor with x
struct BinTrie
{
    static const int B = 30;
    vector<array<int, 2>> nx;
    vi cnt;
    BinTrie() { nx.pb({0, 0}), cnt.pb(0); }
    void insert(int x, int d = 1) // d = -1 erases one copy
    {
        int v = 0;
        cnt[v] += d;
        repb(b, B - 1, 0)
        {
            int c = x >> b & 1;
            if (!nx[v][c]) { nx[v][c] = nx.size(); nx.pb({0, 0}), cnt.pb(0); }
            v = nx[v][c];
            cnt[v] += d;
        }
    }
    int maxXor(int x) // trie must be non-empty
    {
        int v = 0, res = 0;
        repb(b, B - 1, 0)
        {
            int c = x >> b & 1;
            if (nx[v][c ^ 1] && cnt[nx[v][c ^ 1]] > 0) v = nx[v][c ^ 1], res |= 1LL << b;
            else v = nx[v][c];
        }
        return res;
    }
    int minXor(int x)
    {
        int v = 0, res = 0;
        repb(b, B - 1, 0)
        {
            int c = x >> b & 1;
            if (nx[v][c] && cnt[nx[v][c]] > 0) v = nx[v][c];
            else v = nx[v][c ^ 1], res |= 1LL << b;
        }
        return res;
    }
};
