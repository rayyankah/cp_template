// binary trie on numbers < 2^B (BinTrie t(40) for values up to 1e12): insert / erase (multiset) / max xor with x / min xor with x / kth smallest / countLess / countXorLess / values() sorted
struct BinTrie
{
    int B;
    vector<array<int, 2>> nx;
    vi cnt;
    BinTrie(int bits = 30) : B(bits) { nx.pb({0, 0}), cnt.pb(0); }
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
    // ---------- walks down the trie ----------
    int kth(int k) // k-th smallest stored value (1-indexed, copies count), k <= cnt[0]
    {
        int v = 0, res = 0;
        repb(b, B - 1, 0)
        {
            int l = nx[v][0] ? cnt[nx[v][0]] : 0;
            if (k <= l) v = nx[v][0];
            else k -= l, v = nx[v][1], res |= 1LL << b;
        }
        return res;
    }
    int countLess(int x) // stored values < x
    {
        if (x >> B) return cnt[0];
        int v = 0, res = 0;
        repb(b, B - 1, 0)
        {
            int c = x >> b & 1;
            if (c && nx[v][0]) res += cnt[nx[v][0]]; // whole 0-subtree is smaller
            v = nx[v][c];
            if (!v) break;
        }
        return res;
    }
    int countXorLess(int x, int k) // stored y with (x ^ y) < k, x < 2^B
    {
        if (k >> B) return cnt[0];
        int v = 0, res = 0;
        repb(b, B - 1, 0)
        {
            int c = x >> b & 1, kb = k >> b & 1;
            if (kb && nx[v][c]) res += cnt[nx[v][c]]; // xor bit 0 here while k has 1: all smaller
            v = nx[v][c ^ kb];
            if (!v) break;
        }
        return res;
    }
    void walk(int v, int b, int val, vi &out) // all stored values in sorted order (recursive, depth B)
    {
        if (b < 0) { rep(i, 0, cnt[v]) out.pb(val); return; }
        rep(c, 0, 2) if (nx[v][c] && cnt[nx[v][c]] > 0) walk(nx[v][c], b - 1, val | (c << b), out);
    }
    vi values() { vi out; if (cnt[0] > 0) walk(0, B - 1, 0, out); return out; }
};
