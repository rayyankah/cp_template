// suffix array O(n log n) + lcp (kasai). sa = sorted suffix starts, rk = rank of each suffix,
// lcp[i] = lcp(sa[i], sa[i+1]) for i < n-1. lcp of any two suffixes: range min on lcp (sparse table)
// distinct substrings = n(n+1)/2 - sum(lcp)
struct SuffixArray
{
    vi sa, rk, lcp;
    SuffixArray(const string &str)
    {
        string s = str + '\x01'; // sentinel smaller than every character
        int n = s.size(), classes = 256;
        sa.assign(n, 0), rk.assign(n, 0);
        vi cnt(max(classes, n), 0), tmp(n);
        rep(i, 0, n) cnt[(unsigned char)s[i]]++;
        rep(i, 1, classes) cnt[i] += cnt[i - 1];
        repb(i, n - 1, 0) sa[--cnt[(unsigned char)s[i]]] = i;
        rk[sa[0]] = 0, classes = 1;
        rep(i, 1, n) rk[sa[i]] = (s[sa[i]] == s[sa[i - 1]]) ? classes - 1 : classes++;
        for (int h = 1; h < n; h <<= 1)
        {
            rep(i, 0, n) tmp[i] = (sa[i] - h + n) % n;
            fill(cnt.begin(), cnt.begin() + classes, 0);
            rep(i, 0, n) cnt[rk[tmp[i]]]++;
            rep(i, 1, classes) cnt[i] += cnt[i - 1];
            repb(i, n - 1, 0) sa[--cnt[rk[tmp[i]]]] = tmp[i];
            vi nr(n);
            nr[sa[0]] = 0, classes = 1;
            rep(i, 1, n)
            {
                pi cur = {rk[sa[i]], rk[(sa[i] + h) % n]}, prv = {rk[sa[i - 1]], rk[(sa[i - 1] + h) % n]};
                nr[sa[i]] = (cur == prv) ? classes - 1 : classes++;
            }
            rk = nr;
            if (classes == n) break;
        }
        sa.erase(sa.begin()); // drop the sentinel
        n--;
        rk.assign(n, 0);
        rep(i, 0, n) rk[sa[i]] = i;
        lcp.assign(max(0LL, n - 1), 0);
        for (int i = 0, k = 0; i < n; i++)
        {
            if (rk[i] == n - 1) { k = 0; continue; }
            int j = sa[rk[i] + 1];
            while (i + k < n && j + k < n && str[i + k] == str[j + k]) k++;
            lcp[rk[i]] = k;
            if (k) k--;
        }
    }
};
