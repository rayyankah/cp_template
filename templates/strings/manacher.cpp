// manacher: d1[i] = number of odd palindromes centered at i (radius incl. center),
// d2[i] = number of even palindromes centered between i-1 and i. O(n)
// longest palindrome: max over 2*d1[i]-1 and 2*d2[i]
pair<vi, vi> manacher(const string &s)
{
    int n = s.size();
    vi d1(n), d2(n);
    for (int i = 0, l = 0, r = -1; i < n; i++)
    {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) l = i - k, r = i + k;
    }
    for (int i = 0, l = 0, r = -1; i < n; i++)
    {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) l = i - k - 1, r = i + k;
    }
    return {d1, d2};
}
// is s[l..r] a palindrome in O(1) after manacher
bool isPal(const vi &d1, const vi &d2, int l, int r)
{
    int len = r - l + 1, mid = (l + r + 1) / 2;
    return len % 2 ? d1[(l + r) / 2] * 2 - 1 >= len : d2[mid] * 2 >= len;
}
