//stoned game:
void solve() {
    int n;
    cin >> n;
    vi a(n);
    int sum = 0, mx = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
        mx = max(mx, a[i]);
    }
    if (mx > sum - mx) {
        cout << "T" << nl;
    } else {
        cout << ((sum & 1) ? "T" : "HL") << nl;
    }
}
