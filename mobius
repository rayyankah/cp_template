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

// ================ Mobius ================
// Paste below the "Sieve" section. Uses: int(=ll), vi, vpi, rep, repb, pb, all, umap, spf (only sqf_divisors).
// mu / phi / preMu are int32_t on purpose: sieving to 1e7 with long long would cost ~240 MB.

vector<int32_t> mu, phi, preMu; // preMu[i] = mu[1] + ... + mu[i]
vi primes;
void mobius_sieve(int LIM) // linear sieve, O(LIM). call once in main with LIM = max value needed
{
    mu.assign(LIM + 1, 0), phi.assign(LIM + 1, 0), preMu.assign(LIM + 1, 0);
    vector<bool> comp(LIM + 1, false);
    primes.clear();
    mu[1] = phi[1] = 1;
    rep(i, 2, LIM + 1)
    {
        if (!comp[i]) primes.pb(i), mu[i] = -1, phi[i] = i - 1;
        for (int p : primes)
        {
            if (i * p > LIM) break;
            comp[i * p] = true;
            if (i % p == 0) { mu[i * p] = 0, phi[i * p] = phi[i] * p; break; } // p repeats
            mu[i * p] = -mu[i], phi[i * p] = phi[i] * (p - 1);               // new prime
        }
    }
    rep(i, 1, LIM + 1) preMu[i] = preMu[i - 1] + mu[i];
}

int mobius(int n) // mu of ONE big n (up to ~1e12), O(sqrt n), no sieve needed
{
    int res = 1;
    for (int p = 2; p * p <= n; p++)
        if (n % p == 0)
        {
            n /= p;
            if (n % p == 0) return 0;
            res = -res;
        }
    if (n > 1) res = -res;
    return res;
}

// squarefree divisors of x with their mu: {d, mu(d)}. at most 2^7 = 128 of them for x <= 1e6. needs sieve()
// use: #elements coprime to x in a multiset = sum over these of mu(d) * cnt[d]
vpi sqf_divisors(int x)
{
    vpi res = {{1, 1}};
    while (x > 1)
    {
        int p = spf[x];
        while (x % p == 0) x /= p;
        int s = res.size();
        rep(i, 0, s) res.pb({res[i].first * p, -res[i].second});
    }
    return res;
}

// cnt[d] = how many a[i] are divisible by d, d = 1..M. O(M log M)
vi count_multiples(const vi &a, int M)
{
    vi freq(M + 1, 0), cnt(M + 1, 0);
    for (int x : a) freq[x]++;
    rep(d, 1, M + 1) for (int v = d; v <= M; v += d) cnt[d] += freq[v];
    return cnt;
}

// "at least" -> "exactly": input g[d] = #objects with d | gcd, output f[d] = #objects with gcd == d
// descending sieve, O(M log M). works for int or Mint
template <class T> vector<T> exact_from_atleast(vector<T> g)
{
    int M = (int)g.size() - 1;
    repb(d, M, 1) for (int n = 2 * d; n <= M; n += d) g[d] -= g[n];
    return g;
}

// #pairs i<j with gcd(a[i], a[j]) == 1. needs mobius_sieve(>= max a)
int coprime_pairs(const vi &a)
{
    int M = *max_element(all(a));
    vi cnt = count_multiples(a, M);
    int ans = 0;
    rep(d, 1, M + 1) ans += mu[d] * (cnt[d] * (cnt[d] - 1) / 2);
    return ans;
}

// #pairs (x, y), 1<=x<=n, 1<=y<=m, gcd(x,y) == 1. divisor blocks: O(sqrt n + sqrt m) per query
// needs mobius_sieve(>= min(n, m)). for gcd == k call coprime_pairs_range(n / k, m / k)
int coprime_pairs_range(int n, int m)
{
    if (n > m) swap(n, m);
    int ans = 0;
    for (int l = 1, r; l <= n; l = r + 1)
    {
        r = min(n / (n / l), m / (m / l)); // n/d and m/d stay constant for d in [l, r]
        ans += (int)(preMu[r] - preMu[l - 1]) * (n / l) * (m / l);
    }
    return ans;
}

// #squarefree numbers in [1, n]. needs mobius_sieve(>= sqrt n)
int count_squarefree(int n)
{
    int ans = 0;
    for (int d = 1; d * d <= n; d++) ans += mu[d] * (n / (d * d));
    return ans;
}

// sum of gcd(i, j) over ALL ordered pairs 1<=i,j<=n. needs mobius_sieve(n)
// for i<j only: (sum_gcd_all_pairs(n) - n*(n+1)/2) / 2
int sum_gcd_all_pairs(int n)
{
    int ans = 0;
    rep(d, 1, n + 1) ans += (int)phi[d] * (n / d) * (n / d);
    return ans;
}

// Dirichlet convolution h[n] = sum_{d | n} f[d] * g[n / d], indices 1..M. O(M log M). int or Mint
template <class T> vector<T> dirichlet(const vector<T> &f, const vector<T> &g)
{
    int M = (int)f.size() - 1;
    vector<T> h(M + 1, T(0));
    rep(i, 1, M + 1) for (int j = 1; i * j <= M; j++) h[i * j] += f[i] * g[j];
    return h;
}

// Mertens M(n) = mu[1] + ... + mu[n] for n up to ~1e11 (Du's sieve)
// needs mobius_sieve(LIM) with LIM about n^(2/3) (1e6 for n = 1e9, 5e6 for n = 1e10)
umap<int, int> memoMertens;
int mertens(int n)
{
    if (n < (int)preMu.size()) return preMu[n];
    auto it = memoMertens.find(n);
    if (it != memoMertens.end()) return it->second;
    int res = 1; // sum_{i=1..n} M(n / i) = 1
    for (int l = 2, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        res -= (r - l + 1) * mertens(n / l);
    }
    return memoMertens[n] = res;
}

//================ Code starts here ================
// Demo of every Mobius function. Each line prints "got | expected".
// For a real problem, delete the demo and write your solution here.
void solve()
{
    // ---- 1. mobius_sieve: mu[] and phi[] tables ----
    cout << "d    : "; rep(d, 1, 13) cout << setw(3) << d;      cout << nl;
    cout << "mu   : "; rep(d, 1, 13) cout << setw(3) << mu[d];  cout << nl;
    cout << "phi  : "; rep(d, 1, 13) cout << setw(3) << phi[d]; cout << nl;
    cout << "preMu: "; rep(d, 1, 13) cout << setw(3) << preMu[d]; cout << nl;
    // expected mu : 1 -1 -1 0 -1 1 -1 0 0 1 -1 0
    // expected phi: 1 1 2 2 4 2 6 4 6 4 10 4

    // ---- 2. mobius(n): mu of one big number ----
    cout << "mobius(30) = " << mobius(30) << " | -1" << nl;
    cout << "mobius(12) = " << mobius(12) << " | 0" << nl;
    cout << "mobius(200560490130) = " << mobius(200560490130LL) << " | -1  (product of first 11 primes)" << nl;

    // ---- 3. sqf_divisors(x): divisors with nonzero mu ----
    cout << "sqf_divisors(12) = ";
    for (auto [d, m] : sqf_divisors(12)) cout << "(" << d << "," << m << ") ";
    cout << "| (1,1) (2,-1) (3,-1) (6,1)" << nl;

    // ---- 4. count_multiples: cnt[d] for the lesson array ----
    vi a = {2, 3, 4, 6};
    int M = *max_element(all(a));
    vi cnt = count_multiples(a, M);
    cout << "cnt[1..6] = "; rep(d, 1, M + 1) cout << cnt[d] << " "; cout << "| 4 3 2 1 0 1" << nl;

    // ---- 5. coprime_pairs: pairs with gcd 1 ----
    cout << "coprime_pairs({2,3,4,6}) = " << coprime_pairs(a) << " | 2" << nl;

    // ---- 6. exact_from_atleast: g ("both divisible by d") -> f ("gcd exactly d") ----
    vi g(M + 1, 0);
    rep(d, 1, M + 1) g[d] = cnt[d] * (cnt[d] - 1) / 2;   // pairs among multiples of d
    vi f = exact_from_atleast(g);
    cout << "f[1], f[2], f[3] = " << f[1] << " " << f[2] << " " << f[3] << " | 2 3 1" << nl;
    int gcdSum = 0;
    rep(d, 1, M + 1) gcdSum += d * f[d];                  // sum of gcd over all pairs
    cout << "sum of gcd over pairs = " << gcdSum << " | 11" << nl;

    // ---- 6b. same thing with Mint: #non-empty subsets with gcd 1 (CF 803F style) ----
    vector<Mint> gs(M + 1);
    rep(d, 1, M + 1) gs[d] = mexp(Mint(2), cnt[d]) - 1;  // any non-empty subset of multiples of d
    vector<Mint> fs = exact_from_atleast(gs);
    cout << "subsets with gcd 1 = " << fs[1] << " | 6" << nl;

    // ---- 7. coprime_pairs_range: x in [1,n], y in [1,m], gcd 1 (divisor blocks) ----
    cout << "coprime_pairs_range(3, 4) = " << coprime_pairs_range(3, 4) << " | 9" << nl;
    cout << "coprime_pairs_range(6, 6) = " << coprime_pairs_range(6, 6) << " | 23" << nl;
    int n = 6, m = 6, k = 2;                               // gcd == k: divide both by k
    cout << "pairs in 6x6 with gcd 2 = " << coprime_pairs_range(n / k, m / k) << " | 7" << nl;

    // ---- 8. count_squarefree ----
    cout << "count_squarefree(30) = " << count_squarefree(30) << " | 19" << nl;
    cout << "count_squarefree(1e12) = " << count_squarefree(1000000000000LL) << " | 607927102274" << nl;

    // ---- 9. sum_gcd_all_pairs ----
    int s = sum_gcd_all_pairs(3);
    cout << "sum_gcd_all_pairs(3) = " << s << " | 12" << nl;
    cout << "  only i<j: " << (s - 3 * 4 / 2) / 2 << " | 3" << nl;

    // ---- 10. dirichlet: mu * 1 = eps, phi * 1 = id ----
    int L = 12;
    vi muV(L + 1, 0), phiV(L + 1, 0), one(L + 1, 1);
    rep(i, 1, L + 1) muV[i] = mu[i], phiV[i] = phi[i];
    vi e = dirichlet(muV, one), id = dirichlet(phiV, one);
    cout << "mu * 1  = "; rep(i, 1, L + 1) cout << e[i] << " ";  cout << "| 1 0 0 0 ..." << nl;
    cout << "phi * 1 = "; rep(i, 1, L + 1) cout << id[i] << " "; cout << "| 1 2 3 4 ..." << nl;

    // ---- 11. mertens (Du's sieve): mu[1] + ... + mu[n] for huge n ----
    cout << "mertens(1e6) = " << mertens(1000000) << " | 212" << nl;
    cout << "mertens(1e9) = " << mertens(1000000000) << " | -222" << nl;
}

signed main()
{
    fast;
    sieve();                 // needed only for sqf_divisors (uses spf)
    mobius_sieve(1000000);   // LIM = largest value you will look up in mu / phi / preMu
    // compute_factorials();
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
}
