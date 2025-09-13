//holes cf
#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int B = 316;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, m;
    cin >> n >> m;
 
    vector<int> a(n);
    for (int& x : a) {
        cin >> x;
    }
 
    vector<array<int, 2>> nxt(n);
    auto upd = [&](int i) {
        int j = i + a[i];
        if (j < n && i / B == j / B) {
            nxt[i] = {nxt[j][0], nxt[j][1] + 1};
        } else {
            nxt[i] = {j, 1};
        }
    };
    for (int i = n - 1; i >= 0; --i) {
        upd(i);
    }
 
    while (m--) {
        int t, i;
        cin >> t >> i;
        --i;
 
        if (t == 0) {
            int x;
            cin >> x;
 
            a[i] = x;
            for (int j = i; j >= i / B * B; --j) {
                upd(j);
            }
        } else {
            int last = i, ans = 0;
            while (nxt[last][0] < n) {
                ans += nxt[last][1];
                last = nxt[last][0];
            }
            while (true) {
                ++ans;
                if (last + a[last] >= n) {
                    break;
                }
                last = last + a[last];
            }
 
            cout << last + 1 << ' ' << ans << '\n';
        }
    }
}
