//maximum product
void solve()
{
    ll a, b;
    cin >> a >> b;
    string s = to_string(b);
    int len = s.length();
    ll max_prod = 0;
    ll ans = b;
    auto calc_prod = [](string t) -> ll {
        ll p = 1;
        for (char c : t) {
            p *= (c - '0');
        }
        return p;
    };
    auto has_zero = [](ll n) -> bool {
        string str = to_string(n);
        for (char c : str) {
            if (c == '0') return true;
        }
        return false;
    };
    if (!has_zero(b)) {
        max_prod = calc_prod(s);
        ans = b;
    }
    // Special case for leading 1
    if (len > 1 && s[0] == '1') {
        string t(len - 1, '9');
        ll num = stoll(t);
        if (num >= a) {
            ll prod = calc_prod(t);
            if (prod > max_prod) {
                max_prod = prod;
                ans = num;
            }
        }
    }
    // General cases
    for (int i = 0; i < len; i++) {
        if (s[i] > '1') {
            string t = s;
            t[i]--;
            for (int j = i + 1; j < len; j++) {
                t[j] = '9';
            }
            ll num = stoll(t);
            if (num >= a && num <= b) {
                ll prod = calc_prod(t);
                if (prod > max_prod) {
                    max_prod = prod;
                    ans = num;
                }
            }
        }
    }
    cout << ans << nl;
}
