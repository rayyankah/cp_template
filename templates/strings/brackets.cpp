// bracket sequences. balanced(s): every prefix has #'(' >= #')' and the totals are equal
// matchPairs(s): mt[i] = index of the bracket matched with i, or -1. works for ()[]{} mixed
bool balanced(const string &s)
{
    int bal = 0;
    for (char c : s)
    {
        bal += c == '(' ? 1 : -1;
        if (bal < 0) return false;
    }
    return bal == 0;
}
vi matchPairs(const string &s)
{
    int n = s.size();
    vi mt(n, -1), st;
    string open = "([{", close = ")]}";
    rep(i, 0, n)
    {
        if (open.find(s[i]) != string::npos) st.pb(i);
        else if (close.find(s[i]) != string::npos)
        {
            if (!st.empty() && open.find(s[st.back()]) == close.find(s[i])) mt[i] = st.back(), mt[st.back()] = i, st.pop_back();
            else st.clear(); // a wrong closer breaks everything before it
        }
    }
    return mt;
}
// number of balanced sequences of length 2n = catalan(n) = C(2n, n) / (n + 1)
// sequences of length n starting with a fixed prefix (balance b, open so far o): reflection,
// C(rem, k) - C(rem, k + b + 1) with rem = n - |prefix|, k = n/2 - o (closers to place = rem - k)
