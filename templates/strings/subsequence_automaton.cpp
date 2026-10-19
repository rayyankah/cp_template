// nxt[i][c] = smallest j >= i with s[j] == c, or n. jump through it to test "is t a subsequence of s[i..]"
// in O(|t|). lowercase letters; change 26 / 'a' for other alphabets
struct SubseqAutomaton
{
    int n;
    vector<array<int32_t, 26>> nxt;
    SubseqAutomaton(const string &s)
    {
        n = s.size();
        nxt.resize(n + 1);
        nxt[n].fill(n);
        repb(i, n - 1, 0)
        {
            nxt[i] = nxt[i + 1];
            nxt[i][s[i] - 'a'] = i;
        }
    }
    int matchEnd(const string &t, int from = 0) // index right after the greedy match of t, or -1
    {
        int i = from;
        for (char c : t)
        {
            if (i >= n || nxt[i][c - 'a'] == n) return -1;
            i = nxt[i][c - 'a'] + 1;
        }
        return i;
    }
    bool isSubseq(const string &t) { return matchEnd(t) != -1; }
};
