// ================ Author: Rayyan Khalil ================
#define DEBUG   // <-- comment this ONE line to disable every debug(...)

#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using namespace std;

#define ll long long
#define int ll
#define vi vector<int>
#define vvi vector<vector<int>>
#define pi pair<int, int>
#define vpi vector<pair<int, int>>
#define si set<int>
#define mii map<int, int>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define repb(i, a, b) for (int i = a; i >= b; i--)
#define myCeil(a, b) (((a) + (b) - 1) / (b))
#define precise(x) fixed << setprecision(x)
#define nl '\n'
#define fast ios_base::sync_with_stdio(false); cin.tie(nullptr)

const int MOD = 998244353; // or 1000000007
const int N = 1e6 + 10;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int rndRange(int l, int r) { return rnd() % (r - l + 1) + l; } // random in [l,r]

// ================ Debug ================
// debug(x, v, st, mp, ...)  -> prints anything: ints, strings, pairs, vector, set, map, nested...
// debugArr(a, n)            -> prints first n elements of a C array
#ifdef DEBUG
template <class T, class = void> struct is_iterable : false_type {};
template <class T> struct is_iterable<T, void_t<decltype(begin(declval<T &>())), decltype(end(declval<T &>()))>> : true_type {};

template <class A, class B> void _print(const pair<A, B> &p);
template <class T> void _print(const T &x)
{
    if constexpr (is_iterable<T>::value && !is_same_v<T, string>)
    {
        cerr << "{";
        bool first = true;
        for (auto &&e : x)
        {
            if (!first) cerr << ", ";
            first = false;
            _print(e);
        }
        cerr << "}";
    }
    else cerr << x;
}
template <class A, class B> void _print(const pair<A, B> &p)
{
    cerr << "(";
    _print(p.first);
    cerr << ", ";
    _print(p.second);
    cerr << ")";
}
void _dbg() { cerr << nl; }
template <class H, class... T> void _dbg(const H &h, const T &...t)
{
    _print(h);
    if (sizeof...(t)) cerr << " | ";
    _dbg(t...);
}
#define debug(...) cerr << "L" << __LINE__ << " [" << #__VA_ARGS__ << "] = ", _dbg(__VA_ARGS__)
#define debugArr(a, n) cerr << "L" << __LINE__ << " [" << #a << "] = ", _dbg(vector<decay_t<decltype(a[0])>>(a, a + (n)))
#else
#define debug(...)
#define debugArr(a, n)
#endif

template <class T> void read(vector<T> &a) { for (auto &x : a) cin >> x; }

// ================ Math ================
int binExp(int a, int b, int m = MOD)
{
    int res = 1;
    a %= m;
    while (b > 0)
    {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
// a*b % m in O(log b), safe for a, b, m up to 1e18
int binMul(int a, int b, int m)
{
    int res = 0;
    a %= m;
    while (b > 0)
    {
        if (b & 1) res = (res + a) % m;
        a = (a + a) % m;
        b >>= 1;
    }
    return res;
}
int extgcd(int a, int b, int &x, int &y)
{
    if (b == 0) { x = 1, y = 0; return a; }
    int x1, y1;
    int d = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

int fact[N], invFact[N];
void compute_factorials() // call once in main if you need ncr
{
    fact[0] = 1;
    rep(i, 1, N) fact[i] = fact[i - 1] * i % MOD;
    invFact[N - 1] = binExp(fact[N - 1], MOD - 2);
    repb(i, N - 2, 0) invFact[i] = invFact[i + 1] * (i + 1) % MOD;
}
int ncr(int n, int r)
{
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

// ================ Mint ================
struct Mint
{
    int value;
    Mint(ll v = 0) { value = v % MOD; if (value < 0) value += MOD; }
    Mint(ll a, ll b) : value(0) { *this += a; *this /= b; } // a/b mod MOD

    Mint &operator+=(const Mint &b) { value += b.value; if (value >= MOD) value -= MOD; return *this; }
    Mint &operator-=(const Mint &b) { value -= b.value; if (value < 0) value += MOD; return *this; }
    Mint &operator*=(const Mint &b) { value = value * b.value % MOD; return *this; }
    Mint &operator/=(const Mint &b) { return *this *= inverse(b); }

    friend Mint mexp(Mint a, ll e) { Mint res = 1; while (e) { if (e & 1) res *= a; a *= a; e >>= 1; } return res; }
    friend Mint inverse(Mint a) { return mexp(a, MOD - 2); }

    friend Mint operator+(Mint a, const Mint &b) { return a += b; }
    friend Mint operator-(Mint a, const Mint &b) { return a -= b; }
    friend Mint operator*(Mint a, const Mint &b) { return a *= b; }
    friend Mint operator/(Mint a, const Mint &b) { return a /= b; }
    friend Mint operator-(const Mint &a) { return Mint(0) - a; }
    friend bool operator==(const Mint &a, const Mint &b) { return a.value == b.value; }
    friend bool operator!=(const Mint &a, const Mint &b) { return a.value != b.value; }
    friend bool operator<(const Mint &a, const Mint &b) { return a.value < b.value; }
    friend ostream &operator<<(ostream &os, const Mint &a) { return os << a.value; }
};

// ================ Sieve ================
int spf[N];
bool isPrime[N];
vector<vpi> distinct_primes(N); // distinct_primes[x] = {prime, count} of x
vpi factorize(int x);
void sieve() // call once in main
{
    rep(i, 2, N)
    {
        if (spf[i] == 0)
        {
            spf[i] = i;
            isPrime[i] = 1;
            for (int j = i * i; j < N; j += i)
                if (spf[j] == 0) spf[j] = i;
        }
    }
    rep(i, 2, N) distinct_primes[i] = factorize(i);
}
vpi factorize(int x) // {prime, count}, O(log x), needs sieve()
{
    vpi res;
    while (x > 1)
    {
        int p = spf[x], cnt = 0;
        while (x % p == 0) x /= p, cnt++;
        res.pb({p, cnt});
    }
    return res;
}

// ================ Anti-hack unordered_map ================
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template <class K, class V> using umap = unordered_map<K, V, custom_hash>;
template <class T> using uset = unordered_set<T, custom_hash>;

//================ Code starts here ================
void solve()
{

}

signed main()
{
    fast;
    // sieve();
    // compute_factorials();
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
}
