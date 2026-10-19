// z function: z[i] = longest common prefix of s and s[i..]; z[0] = n
// occurrences of pat in text: z of pat + '#' + text, positions with z == |pat|
vi zFunction(const string &s)
{
    int n = s.size();
    vi z(n, 0);
    if (n) z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; i++)
    {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}
