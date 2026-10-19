// aho corasick over 'a'..'z'. AhoCorasick ac; id = ac.add(word); ac.build();
// walk: v = ac.go[v][c]. ac.out[v] = number of words ending at v or at any suffix link of v (after build)
// to list matches, follow ac.dict[v] (next node on the suffix-link chain that ends a word)
// ac.bfs = nodes in bfs order (increasing depth): to push values up the suffix links, loop it backwards
struct AhoCorasick
{
    vector<array<int32_t, 26>> go; // int32 keeps memory low
    vi link, out, dict, endHere, bfs;
    AhoCorasick() { node(); }
    int node()
    {
        go.pb({}), go.back().fill(-1);
        link.pb(0), out.pb(0), dict.pb(-1), endHere.pb(0);
        return go.size() - 1;
    }
    int add(const string &w)
    {
        int v = 0;
        for (char ch : w)
        {
            int c = ch - 'a';
            if (go[v][c] == -1) { int u = node(); go[v][c] = u; }
            v = go[v][c];
        }
        endHere[v]++, out[v]++;
        return v;
    }
    void build() // bfs, turns go[][] into a full automaton
    {
        queue<int> q;
        bfs = {0};
        rep(c, 0, 26)
        {
            if (go[0][c] == -1) go[0][c] = 0;
            else link[go[0][c]] = 0, q.push(go[0][c]);
        }
        while (!q.empty())
        {
            int v = q.front(); q.pop();
            bfs.pb(v);
            out[v] += out[link[v]];
            dict[v] = endHere[link[v]] ? link[v] : dict[link[v]];
            rep(c, 0, 26)
            {
                int u = go[v][c];
                if (u == -1) go[v][c] = go[link[v]][c];
                else link[u] = go[link[v]][c], q.push(u);
            }
        }
    }
};
