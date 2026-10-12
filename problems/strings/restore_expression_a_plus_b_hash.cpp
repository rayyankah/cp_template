//cf -->2300
//================ Code starts here ================
struct NumHash {
    static const int MOD1 = 1000000007;
    static const int MOD2 = 1000000009;
    vector<int> p1, p2, h1, h2;
    string s;
    int n;

    void build(const string& str) {
        s = str;
        n = (int)s.size();
        p1.assign(n + 1, 0); p2.assign(n + 1, 0);
        h1.assign(n + 1, 0); h2.assign(n + 1, 0);
        p1[0] = p2[0] = 1;
        for (int i = 0; i < n; ++i) {
            int d = s[i] - '0';
            p1[i + 1] = (p1[i] * 10) % MOD1;
            p2[i + 1] = (p2[i] * 10) % MOD2;
            h1[i + 1] = ( (h1[i] * 10) % MOD1 + d ) % MOD1;
            h2[i + 1] = ( (h2[i] * 10) % MOD2 + d ) % MOD2;
        }
    }

    inline int get1(int l, int r) { 
        int len = r - l + 1;
        int val = (h1[r + 1] - (h1[l] * p1[len]) % MOD1);
        if (val < 0) val += MOD1;
        return val;
    }
    inline int get2(int l, int r) { 
        int len = r - l + 1;
        int val = (h2[r + 1] - (h2[l] * p2[len]) % MOD2);
        if (val < 0) val += MOD2;
        return val;
    }
};

int n;
string s;
NumHash H;

bool leading_ok(int l, int len) {
    return len == 1 || s[l] != '0';
}

bool sum_equals_c(int aL, int aR, int bL, int bR, int cL, int cR) {
    int i = aR, j = bR, k = cR, carry = 0;
    while (i >= aL || j >= bL) {
        int da = (i >= aL) ? (s[i] - '0') : 0;
        int db = (j >= bL) ? (s[j] - '0') : 0;
        int sum = da + db + carry;
        if (k < cL) return false;
        int dc = s[k] - '0';
        if ((sum % 10) != dc) return false;
        carry = sum / 10;
        --i; --j; --k;
    }
    if (carry) {
        if (k < cL) return false;
        if ((s[k] - '0') != carry) return false;
        --k;
    }
    return k < cL;
}

bool try_split(int len1, int len2, int len3) {
    if (len1 <= 0 || len2 <= 0 || len3 <= 0) return false;
    if (len1 + len2 + len3 != n) return false;

    int aL = 0, aR = len1 - 1;
    int bL = len1, bR = len1 + len2 - 1;
    int cL = len1 + len2, cR = n - 1;

    if (!leading_ok(aL, len1)) return false;
    if (!leading_ok(bL, len2)) return false;
    if (!leading_ok(cL, len3)) return false;

    int a1 = H.get1(aL, aR), b1 = H.get1(bL, bR), c1 = H.get1(cL, cR);
    int a2 = H.get2(aL, aR), b2 = H.get2(bL, bR), c2 = H.get2(cL, cR);

    if ( ((a1 + b1) % NumHash::MOD1 == c1) && ((a2 + b2) % NumHash::MOD2 == c2) ) {
        if (sum_equals_c(aL, aR, bL, bR, cL, cR)) {
            cout << s.substr(0, len1) << "+" << s.substr(len1, len2) << "=" << s.substr(len1 + len2) << nl;
            return true;
        }
    }
    return false;
}

void solve() {
    cin >> s;
    n = (int)s.size();
    H.build(s);

    for (int len3 = 1; len3 <= n; ++len3) {
        if (try_split(len3, n - len3 - len3, len3)) return;
        if (try_split(len3 - 1, n - (len3 - 1) - len3, len3)) return;
        if (try_split(n - len3 - len3, len3, len3)) return;
        if (try_split(n - (len3 - 1) - len3, len3 - 1, len3)) return;
    }

}
