// very fast input for 1e6+ numbers or huge strings (faster than cin with sync off).
// use readInt() everywhere instead of cin >> for numbers. do not mix with cin on the same input
static char ibuf[1 << 25];
size_t ipos = 0, ilen = 0;
inline int gc() { if (ipos == ilen) { ilen = fread(ibuf, 1, sizeof(ibuf), stdin); ipos = 0; if (!ilen) return -1; } return ibuf[ipos++]; }
inline int readInt()
{
    int c = gc();
    while (c != '-' && (c < '0' || c > '9')) c = gc();
    bool neg = false;
    if (c == '-') neg = true, c = gc();
    int x = 0;
    while (c >= '0' && c <= '9') x = x * 10 + (c - '0'), c = gc();
    return neg ? -x : x;
}
inline string readToken() { string s; int c = gc(); while (c == ' ' || c == '\n' || c == '\r') c = gc(); while (c != -1 && c != ' ' && c != '\n' && c != '\r') s += char(c), c = gc(); return s; }
// output: build one string / use '\n' not endl, and printf / cout with sync off is fine
