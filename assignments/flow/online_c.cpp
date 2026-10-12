// c online
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
// rnd()  generates a random number
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
// random number within a range [l,r]
int rndRange(int l, int r) { return rnd() % (r - l + 1) + l; }

//================ Code starts here ================
void solve()
{
    int m, n;
    cin >> m >> n;
    vvi gang(m, vi(7));
    vvi partner(n, vi(7));
    rep(i, 0, m)
    {
        rep(j, 0, 7)
        {
            cin >> gang[i][j];
        }
    }
    rep(i, 0, n)
    {
        rep(j, 0, 7)
        {
            cin >> partner[i][j];
        }
    }
    int h = n;
    vvi adj(h + m + 2);
    vvi capacity(h + m + 2, vi(h + m + 2, 0));
    vvi original(h + m + 2, vi(h + m + 2, 0));
    function<bool(int, int)> possible = [&](int i, int j)
    {
        int exp1 = gang[i][0];
        int exp2 = partner[j][0];
        int age1 = gang[i][1];
        int age2 = partner[j][1];
        int crim1 = gang[i][2];
        int crim2 = partner[j][2];
        int orig1 = gang[i][3];
        int orig2 = partner[j][3];
        int prof1 = gang[i][4];
        int prof2 = partner[j][4];
        int trust1 = gang[i][5];
        int trust2 = partner[j][5];
        int lang1 = (gang[i][6]);
        int lang2 = (partner[j][6]);
        if (abs(exp1 - exp2) > 12)
            return false;
        if (abs(age1 - age2) > 5)
            return false;
        if (!((crim1 && crim2) || (!crim1 && !crim2)))
            return false;
        if (!(((orig1 && orig2) || (!orig1 && !orig2))))
            return false;
        if (!prof1 && !prof2)
            return false;
        if (trust1 + trust2 < 10)
            return false;
        rep(i, 0, 10)
        {
            if ((1 << i) & lang1 && (1 << i) & lang2)
            {
                return true;
            }
        }

        return false;
    };

    rep(i, 0, m)
    {
        rep(j, 0, h)
        {
            int idx = j + m;

            if (possible(i,j))
            {
                adj[i].pb(j + m);
                adj[j + m].pb(i);
                capacity[i][j + m] = 1;
                original[i][j + m] = 1;
            }
        }
    }
    int flow = 0;
    int s = m + h;
    int t = m + h + 1;
    rep(i, 0, m)
    {
        adj[i].pb(s);
        adj[s].pb(i);
        capacity[s][i] = 1;
        original[s][i] = 1;
    }
    rep(i, 0, h)
    {
        int j = i + m;
        adj[j].pb(t);
        adj[t].pb(j);
        capacity[j][t] =1;
        // original[j][t] += 1;
    }
    
}

signed main()
{
    fast;

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
}
