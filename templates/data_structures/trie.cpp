// trie on lowercase strings, arrays instead of pointers (fast, no leaks). node 0 = root (empty string).
// Trie t; t.insert(s); t.erase(s) (multiset); t.count(s); t.prefixCount(p); t.find(p) = node or -1
// pass[v] = words in v's subtree, ends[v] = words ending exactly at v, dep/par/ch rebuild the string of v
// traversals: words() = all words sorted (dfs), kth(k) = k-th smallest word, levels() = nodes by depth (bfs),
// euler() = tin/tout so v's subtree is the range [tin[v], tout[v]] (subtree queries with a segment tree)
struct Trie
{
    static const int A = 26;
    vector<array<int, A>> nx;
    vi pass, ends, dep, par, ch;
    Trie() { newNode(-1, -1); }
    int newNode(int p, int c)
    {
        nx.pb({}), nx.back().fill(-1);
        pass.pb(0), ends.pb(0), dep.pb(p < 0 ? 0 : dep[p] + 1), par.pb(p), ch.pb(c);
        return nx.size() - 1;
    }
    int size() { return nx.size(); }
    void insert(const string &s, int d = 1) // d = -1 removes one copy (word must exist)
    {
        int v = 0;
        pass[v] += d;
        for (char c : s)
        {
            int x = c - 'a';
            if (nx[v][x] < 0) { int u = newNode(v, x); nx[v][x] = u; }
            v = nx[v][x], pass[v] += d;
        }
        ends[v] += d;
    }
    void erase(const string &s) { if (count(s)) insert(s, -1); }
    int find(const string &p) // node spelling p, or -1
    {
        int v = 0;
        for (char c : p)
        {
            v = nx[v][c - 'a'];
            if (v < 0 || pass[v] == 0) return -1;
        }
        return v;
    }
    int count(const string &s) { int v = find(s); return v < 0 ? 0 : ends[v]; }      // copies of s
    int prefixCount(const string &p) { int v = find(p); return v < 0 ? 0 : pass[v]; } // words starting with p
    int lcpWith(const string &s) // longest prefix of s that is a prefix of some word
    {
        int v = 0, d = 0;
        for (char c : s)
        {
            int u = nx[v][c - 'a'];
            if (u < 0 || pass[u] == 0) break;
            v = u, d++;
        }
        return d;
    }
    string str(int v) // the string spelled by node v
    {
        string s;
        for (; v > 0; v = par[v]) s += char('a' + ch[v]);
        reverse(all(s));
        return s;
    }
    // ---------- traversals ----------
    vector<string> words(int from = 0) // every word in from's subtree, sorted, with repeats (iterative dfs)
    {
        vector<string> res;
        string cur = str(from);
        vector<pi> st = {{from, 0}}; // (node, next child to try)
        rep(i, 0, ends[from]) res.pb(cur);
        while (!st.empty())
        {
            int v = st.back().first, &c = st.back().second;
            while (c < A && (nx[v][c] < 0 || pass[nx[v][c]] == 0)) c++;
            if (c == A) { st.pop_back(); if (!cur.empty() && !st.empty()) cur.pop_back(); continue; }
            int u = nx[v][c++];
            cur += char('a' + ch[u]);
            rep(i, 0, ends[u]) res.pb(cur);
            st.pb({u, 0});
        }
        return res;
    }
    string kth(int k) // k-th smallest word (1-indexed, repeats count), k <= pass[0]
    {
        int v = 0;
        string s;
        while (true)
        {
            if (k <= ends[v]) return s;
            k -= ends[v];
            rep(c, 0, A)
            {
                int u = nx[v][c];
                if (u < 0) continue;
                if (k <= pass[u]) { v = u, s += char('a' + c); break; }
                k -= pass[u];
            }
        }
    }
    vi levels() // nodes in bfs order: depth by depth, each depth in lexicographic order
    {
        vi q = {0};
        rep(i, 0, (int)q.size()) rep(c, 0, A) if (nx[q[i]][c] >= 0) q.pb(nx[q[i]][c]);
        return q;
    }
    vi tin, tout;
    void euler() // preorder positions: subtree of v = [tin[v], tout[v]]. bottom-up dp: loop levels() backwards
    {
        int n = size(), t = 0;
        tin.assign(n, 0), tout.assign(n, 0);
        vector<pi> st = {{0, 0}};
        tin[0] = t++;
        while (!st.empty())
        {
            int v = st.back().first, &c = st.back().second;
            while (c < A && nx[v][c] < 0) c++;
            if (c == A) { tout[v] = t - 1, st.pop_back(); continue; }
            int u = nx[v][c++];
            tin[u] = t++, st.pb({u, 0});
        }
    }
};
// examples:
//   for (int v : t.levels()) {...}                       top-down dp (parent before child)
//   vi o = t.levels(); reverse(all(o)); for (int v : o)  bottom-up dp (children before parent)
//   t.words(t.find(p))                                   all words with prefix p, sorted
