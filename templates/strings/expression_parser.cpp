// recursive descent: + - * / and parentheses, integers, left-to-right, usual priority
// pos must be 0 before evaluate(s). handles unary minus: "-(2+3)*4"
int pos;
int parseExpr(const string &s);
int parseAtom(const string &s)
{
    if (s[pos] == '-') { pos++; return -parseAtom(s); }
    if (s[pos] == '(')
    {
        pos++;
        int v = parseExpr(s);
        pos++; // skip ')'
        return v;
    }
    int v = 0;
    while (pos < (int)s.size() && isdigit(s[pos])) v = v * 10 + (s[pos++] - '0');
    return v;
}
int parseTerm(const string &s)
{
    int v = parseAtom(s);
    while (pos < (int)s.size() && (s[pos] == '*' || s[pos] == '/'))
    {
        char op = s[pos++];
        int r = parseAtom(s);
        v = op == '*' ? v * r : v / r;
    }
    return v;
}
int parseExpr(const string &s)
{
    int v = parseTerm(s);
    while (pos < (int)s.size() && (s[pos] == '+' || s[pos] == '-'))
    {
        char op = s[pos++];
        int r = parseTerm(s);
        v = op == '+' ? v + r : v - r;
    }
    return v;
}
int evaluate(string s)
{
    s.erase(remove(all(s), ' '), s.end());
    pos = 0;
    return parseExpr(s);
}
