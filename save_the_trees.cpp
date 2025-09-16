// ================ Author: Rayyan Khalil ================

#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
using namespace std;

#define vvi vector<vector<int>>
#define vll vector<long long>
#define si set<int>
#define mii map<int, int>
#define vi vector<int>
#define vpi vector<pair<int, int>>
#define pi pair<int, int>
#define ll long long
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define tk_input(a) rep(i, 0, n) cin >> a[i]
#define repb(i, a, b) for (int i = a; i >= b; i--)
#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

#ifdef DEBUG
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_print(__VA_ARGS__)
void debug_print() { cerr << endl; }
template <typename T, typename... Args>
void debug_print(T t, Args... args)
{
    cerr << t;
    if (sizeof...(args))
        cerr << ", ";
    debug_print(args...);
}
#else
#define debug(...)
#endif

#define myCeil(a, b) (a + b - 1) / b
const int MOD = 1000000007;
#define nl '\n'
#define precise(x) fixed << setprecision(x)
#define int ll
int binMul(int a, int b, int m)
{
    int res = 0;
    a %= m;
    while (b > 0)
    {
        if (b & 1)
        {
            res = (res + a) % m;
        }
        a = (a + a) % m;
        b >>= 1;
    }
    return res;
}

int binExp(int a, int b)
{
    int res = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            res = (1LL * res * a) % MOD;
        }
        a = (1LL * a * a) % MOD;
        b >>= 1;
    }
    return res;
}
int extended_euclidean_gcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extended_euclidean_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

template <class T>
using vv = vector<vector<T>>;
template <class T>
using v = vector<T>;

// ------------------ SAFE unordered_map helpers ------------------
struct custom_hash
{
    static inline uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const noexcept
    {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return (size_t)splitmix64(x + FIXED_RANDOM);
    }
};

template <class K, class V>
using umap = unordered_map<K, V, custom_hash>;
template <class T>
using uset = unordered_set<T, custom_hash>;

template <class Map>
inline void secure_reserve(Map &m, size_t expected_size, float lf = 0.25f)
{
    m.max_load_factor(lf);
    m.reserve(expected_size);
}

template <class T>
void read(vector<T> &a)
{
    for (auto &x : a)
        cin >> x;
}
template <class T>
void read(vv<T> &a)
{
    for (auto &r : a)
        for (auto &x : r)
            cin >> x;
}

template <class A, class B>
ostream &operator<<(ostream &os, const pair<A, B> &p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &a)
{
    os << "[";
    string s = "";
    for (auto &x : a)
    {
        os << s << x;
        s = ", ";
    }
    os << "]";
    return os;
}
template <class T>
ostream &operator<<(ostream &os, const set<T> &a)
{
    os << "{";
    string s = "";
    for (auto &x : a)
    {
        os << s << x;
        s = ", ";
    }
    os << "}";
    return os;
}
template <class T>
ostream &operator<<(ostream &os, const multiset<T> &a)
{
    os << "{";
    string s = "";
    for (auto &x : a)
    {
        os << s << x;
        s = ", ";
    }
    os << "}";
    return os;
}
template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &a)
{
    os << "{";
    string s = "";
    for (auto &kv : a)
    {
        os << s << kv.first << ": " << kv.second;
        s = ", ";
    }
    os << "}";
    return os;
}

template <class K, class V, class H, class Eq, class Alloc>
ostream &operator<<(ostream &os, const unordered_map<K, V, H, Eq, Alloc> &a)
{
    os << "{";
    string s = "";
    for (auto &kv : a)
    {
        os << s << kv.first << ": " << kv.second;
        s = ", ";
    }
    os << "}";
    return os;
}
template <class T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &a)
{
    os << "[";
    string s = "";
    for (auto &x : a)
    {
        os << s << x;
        s = ", ";
    }
    os << "]";
    return os;
}

// template<typename T>
// using ordered_set = tree<T, null_type, //less<T>, rb_tree_tag, //tree_order_statistics_node_update>;
// ans+=b.size()-b.order_of_key(in[i].second+1);

template <class T>
void debug_print_array(vector<T> &arr)
{
    for (auto &elem : arr)
    {
        cerr << elem << " ";
    }
    cerr << endl;
}
const int N = 1e6 + 10;
vi factorial(N);
vi inv(N);
void compute_factorials()
{
    factorial[0] = 1;
    for (int i = 1; i < N; i++)
    {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    inv[N - 1] = binExp(factorial[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--)
    {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;
    }
}
int ncr(int n, int r)
{
    if (r > n || r < 0)
        return 0;

    return (binMul(factorial[n], binMul(inv[r], inv[n - r], MOD), MOD));
}
const int maxN = 2e5 + 10;
int type[maxN];
int height[maxN];
int seg[4 * maxN];
int lazy[4 * maxN];
void build(int idx, int l, int r)
{
    lazy[idx] = 0;
    if (l == r)
    {
        seg[idx] = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(2 * idx + 1, l, mid);
    build(2 * idx + 2, mid + 1, r);
    seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
}

void rangeUpdate(int idx, int l, int r, int ql, int qr, int val_to_add)
{
    if (lazy[idx] != 0)
    {
        seg[idx] += lazy[idx];
        if (l != r)
        {
            lazy[2 * idx + 1] += lazy[idx];
            lazy[2 * idx + 2] += lazy[idx];
        }
        lazy[idx] = 0;
    }
    if (l > qr || r < ql || l > r)
        return;
    if (l >= ql && r <= qr)
    {
        seg[idx] += val_to_add; // no (r-l+1)*val cz we don't want sum we want max
        if (l != r)
        {
            lazy[2 * idx + 1] += val_to_add;
            lazy[2 * idx + 2] += val_to_add;
        }
        return;
    }
    int mid = (l + r) / 2;
    rangeUpdate(2 * idx + 1, l, mid, ql, qr, val_to_add);
    rangeUpdate(2 * idx + 2, mid + 1, r, ql, qr, val_to_add);
    seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
    return;
}
int queryMinLazy(int idx, int l, int r, int ql, int qr)
{
    if (lazy[idx] != 0)
    {
        seg[idx] += lazy[idx];
        if (l != r)
        {
            lazy[2 * idx + 1] += lazy[idx];
            lazy[2 * idx + 2] += lazy[idx];
        }
        lazy[idx] = 0;
    }
    if (l > qr || r < ql || l > r)
        return 1e15;
    if (l >= ql && r <= qr)
    {
        return seg[idx];
    }
    int mid = (l + r) / 2;
    int left = queryMinLazy(2 * idx + 1, l, mid, ql, qr);
    int right = queryMinLazy(2 * idx + 2, mid + 1, r, ql, qr);
    return min(left, right);
}

//================ Code starts here ================
void solve()
{
    // memset(seg, 0, sizeof(seg));
    // memset(height, 0, sizeof(height));
    // memset(type, 0, sizeof(type));

    int n;
    cin >> n;

    // memset(lazy, 0, sizeof(lazy));

    rep(i, 1, n + 1)
    {
        cin >> type[i] >> height[i];
    }
    build(0, 1, n);
    int leftmost[n + 1];
    leftmost[0] = 0;
    rep(i, 1, n + 1)
    {
        leftmost[i] = i;
    }
    int i = n;
    umap<int, int> last_pos;
    secure_reserve(last_pos, n);
    // bulding this leftmost in O(n) time
    rep(i, 1, n + 1)
    {
        if (last_pos.count(type[i]))
        {
            leftmost[i] = max(last_pos[type[i]] + 1, leftmost[i - 1]);
        }
        else
        {
            leftmost[i] = leftmost[i - 1];
        }
        last_pos[type[i]] = i;
    }
    // rep(i,1,n+1){
    //     debug(i,leftmost[i]);
    // }
    height[0] = INT_MAX;
    stack<int> mx;
    mx.push(0);
    int dp[n + 1];
    rep(i, 1, n + 1)
    {
        while (height[i] >height[mx.top()])
        {
            int currpos = mx.top();
            mx.pop();
            int prevpos = mx.empty() ? 0 : mx.top();
            rangeUpdate(0, 1, n, prevpos + 1, currpos, -height[currpos]);
            // helpoer[j] = dp[j-1]+rangeMax(j..i);
        }
        rangeUpdate(0, 1, n, mx.top() + 1, i, height[i]);
        mx.push(i);
        dp[i] = queryMinLazy(0, 1, n, leftmost[i], i);
        rangeUpdate(0, 1, n, i + 1, i + 1, dp[i]);
        // helper[i]=dp[i-1].....
    }
    cout << dp[n] << nl;
}

signed main()
{
    fast;

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        cout << "Case " << i << ": ";
        solve();
    }
}
