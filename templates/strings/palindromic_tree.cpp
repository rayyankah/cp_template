// palindromic tree (eertree). Eertree t(n); t.add(c) for each char of s in order ('a'..'z')
// t.add returns the node of the longest palindromic suffix. node 0: len -1 root, node 1: len 0 root
// number of distinct palindromes = t.len.size() - 2. cnt[v] (after t.count()) = occurrences of node v's palindrome
struct Eertree
{
    vector<array<int, 26>> nx;
    vi len, link, cnt;
    string s;
    int last = 1;
    Eertree(int n = 0)
    {
        nx.reserve(n + 2);
        nx.pb({}), nx.pb({});
        nx[0].fill(0), nx[1].fill(0);
        len = {-1, 0}, link = {0, 0}, cnt = {0, 0};
    }
    int getLink(int v, int i)
    {
        while (i - 1 - len[v] < 0 || s[i - 1 - len[v]] != s[i]) v = link[v];
        return v;
    }
    int add(char ch)
    {
        s.pb(ch);
        int i = s.size() - 1, c = ch - 'a';
        int v = getLink(last, i);
        if (!nx[v][c])
        {
            int u = nx.size();
            nx.pb({}), nx.back().fill(0);
            len.pb(len[v] + 2), cnt.pb(0);
            link.pb(len.back() == 1 ? 1 : nx[getLink(link[v], i)][c]);
            nx[v][c] = u;
        }
        last = nx[v][c];
        cnt[last]++;
        return last;
    }
    void count() { repb(v, (int)len.size() - 1, 2) cnt[link[v]] += cnt[v]; }
};
