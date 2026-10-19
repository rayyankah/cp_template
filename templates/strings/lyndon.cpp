// duval: lyndon factorization of s into s = w1 w2 ... wk with w1 >= w2 >= ... (each wi is a lyndon word). O(n)
// returns the start index of each factor. smallest rotation: run on s + s, take the factor start < n with the longest reach
vi duval(const string &s)
{
    int n = s.size(), i = 0;
    vi starts;
    while (i < n)
    {
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j])
        {
            if (s[k] < s[j]) k = i; else k++;
            j++;
        }
        while (i <= k) starts.pb(i), i += j - k;
    }
    return starts;
}
