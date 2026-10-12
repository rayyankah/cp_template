//longest pallindromic substring

void solve() {

    string s;
    int x;
    cin >>x;
    cin>>s;
    int n = (int)s.size();

    const long long M1 = 1000000007LL, M2 = 1000000009LL;
    const long long B1 = 911382323LL, B2 = 972663749LL;

    vector<long long> pow1(n + 1, 1), pow2(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        pow1[i] = (pow1[i - 1] * B1) % M1;
        pow2[i] = (pow2[i - 1] * B2) % M2;
    }

    auto buildPref = [&](const string& a) {
        vector<long long> p1(n + 1, 0), p2(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            p1[i + 1] = (p1[i] * B1 + (a[i] - 'a' + 1)) % M1;
            p2[i + 1] = (p2[i] * B2 + (a[i] - 'a' + 1)) % M2;
        }
        return pair<vector<long long>, vector<long long>>(move(p1), move(p2));
    };

    string t = s;
    reverse(t.begin(), t.end());

    auto pres = buildPref(s);
    auto rpres = buildPref(t);
    const vector<long long>& pre1 = pres.first;
    const vector<long long>& pre2 = pres.second;
    const vector<long long>& rpre1 = rpres.first;
    const vector<long long>& rpre2 = rpres.second;

    auto getHash = [&](const vector<long long>& p, const vector<long long>& pw, int l, int r, long long mod) {
        long long res = (p[r + 1] - (p[l] * pw[r - l + 1]) % mod);
        if (res < 0) res += mod;
        return res;
    };

    auto isPal = [&](int l, int r) {
        if (l > r) return true;
        int rl = n - 1 - r, rr = n - 1 - l;
        long long a1 = getHash(pre1, pow1, l, r, M1);
        long long a2 = getHash(pre2, pow2, l, r, M2);
        long long b1 = getHash(rpre1, pow1, rl, rr, M1);
        long long b2 = getHash(rpre2, pow2, rl, rr, M2);
        return a1 == b1 && a2 == b2;
    };

    auto oddRadius = [&](int c) {
        int lo = 0, hi = min(c, n - 1 - c), ans = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (isPal(c - mid, c + mid)) { ans = mid; lo = mid + 1; }
            else hi = mid - 1;
        }
        return ans;
    };

    auto evenRadius = [&](int i) {
        int lo = 0, hi = min(i + 1, n - 1 - i), ans = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            int l = i - mid + 1, r = i + mid;
            if (l <= r && isPal(l, r)) { ans = mid; lo = mid + 1; }
            else hi = mid - 1;
        }
        return ans;
    };

    int best = 0;
    for (int i = 0; i < n; ++i) {
        int o = oddRadius(i);
        int e = (i + 1 < n) ? evenRadius(i) : 0;
        best = max(best, max(2 * o + 1, 2 * e));
    }

    cout << best << "\n";
}
