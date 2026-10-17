struct palindrome_tracker
{
    const int p1 = 31, m1 = 1e9 + 7, inv1 = 129032259;
    const int p2 = 37, m2 = 1e9 + 9, inv2 = 297297300;
    int f1 = 0, r1 = 0, pw1 = 1;
    int f2 = 0, r2 = 0, pw2 = 1;
    string s;

    void push_back(char ch)
    {
        int c = ch;
        f1 = (f1 * p1 + c) % m1;
        f2 = (f2 * p2 + c) % m2;
        r1 = (r1 + c * pw1) % m1;
        r2 = (r2 + c * pw2) % m2;
        pw1 = pw1 * p1 % m1;
        pw2 = pw2 * p2 % m2;
        s.pb(ch);
    }

    void pop_back()
    {
        int c = s.back();
        s.pop_back();
        pw1 = pw1 * inv1 % m1;
        pw2 = pw2 * inv2 % m2;
        r1 = ((r1 - c * pw1) % m1 + m1) % m1;
        r2 = ((r2 - c * pw2) % m2 + m2) % m2;
        f1 = (f1 - c + m1) % m1 * inv1 % m1;
        f2 = (f2 - c + m2) % m2 * inv2 % m2;
    }

    bool is_palindrome() const { return f1 == r1 && f2 == r2; }
    bool empty() const { return s.empty(); }
    int size() const { return s.size(); }
};
