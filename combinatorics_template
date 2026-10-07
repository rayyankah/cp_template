// ================ Author: Rayyan Khalil ================
#define DEBUG

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

const int MOD = 998244353;
const int N = 1e6 + 10;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int rndRange(int l, int r) { return rnd() % (r - l + 1) + l; }

// ================ Debug ================
#ifdef DEBUG
template <class... Ts> struct make_void_ { typedef void type; };
template <class... Ts> using void_t_ = typename make_void_<Ts...>::type;
template <class T, class = void> struct is_iterable : false_type {};
template <class T> struct is_iterable<T, void_t_<decltype(begin(declval<T &>())), decltype(end(declval<T &>()))>> : true_type {};

void _print(const string &s);
void _print(const char *s);
template <class A, class B> void _print(const pair<A, B> &p);
template <class T> void _print(const T &x);

void _print(const string &s) { cerr << s; }
void _print(const char *s) { cerr << s; }
template <class A, class B> void _print(const pair<A, B> &p)
{
    cerr << "(";
    _print(p.first);
    cerr << ", ";
    _print(p.second);
    cerr << ")";
}
template <class T> void _print_impl(const T &x, true_type)
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
template <class T> void _print_impl(const T &x, false_type) { cerr << x; }
template <class T> void _print(const T &x) { _print_impl(x, integral_constant<bool, is_iterable<T>::value>()); }

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
void compute_factorials()
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
    Mint(ll a, ll b) : value(0) { *this += a; *this /= b; }

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

// ================ Combinatorics ================
// Call compute_factorials() first. Everything is mod MOD (must be prime) unless a modulus is passed.
// Every function returns 0 for impossible arguments (r < 0, r > n, negative totals).

// ---- basics ----
int modInv(int a) { return binExp((a % MOD + MOD) % MOD, MOD - 2); } // a must be non-zero mod MOD
int invNum(int n) { return invFact[n] * fact[n - 1] % MOD; }           // 1/n for 1 <= n < N, O(1)
int npr(int n, int r) { return (r < 0 || r > n) ? 0 : fact[n] * invFact[n - r] % MOD; }
int multinomial(const vi &cnt)                                           // (sum c)! / prod c!
{
    int s = 0, res = 1;
    for (int c : cnt) s += c, res = res * invFact[c] % MOD;
    return fact[s] * res % MOD;
}
int ncrBig(int n, int r)                                                 // n up to 1e18, r < N and r < MOD
{
    if (r < 0 || r > n) return 0;
    int num = 1;
    rep(i, 0, r) num = num * ((n - i) % MOD) % MOD;
    return num * invFact[r] % MOD;
}
vector<vector<int32_t>> pascal(int K, int m)                            // C[n][r] for n <= K, ANY modulus m
{                                                                        // int32 storage: K = 5000 is ~100 MB
    vector<vector<int32_t>> C(K + 1, vector<int32_t>(K + 1, 0));
    rep(i, 0, K + 1)
    {
        C[i][0] = 1 % m;
        rep(j, 1, i + 1) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % m;
    }
    return C;
}
struct Lucas                                                             // C(n, r) mod small prime p, n, r up to 1e18
{
    int p; vi f, fi;
    Lucas(int p_) : p(p_), f(p_), fi(p_)
    {
        f[0] = 1;
        rep(i, 1, p) f[i] = f[i - 1] * i % p;
        fi[p - 1] = binExp(f[p - 1], p - 2, p);
        repb(i, p - 1, 1) fi[i - 1] = fi[i] * i % p;
    }
    int small(int n, int r) { return r > n ? 0 : f[n] * fi[r] % p * fi[n - r] % p; }
    int C(int n, int r)
    {
        if (r < 0 || r > n) return 0;
        int res = 1;
        while ((n || r) && res) res = res * small(n % p, r % p) % p, n /= p, r /= p;
        return res;
    }
};

// ---- stars and bars ----
int starsBars(int n, int k)                                              // x1+..+xk = n, xi >= 0
{
    if (n < 0 || k < 0) return 0;
    if (k == 0) return n == 0;
    return ncr(n + k - 1, k - 1);
}
int starsBarsPos(int n, int k) { return starsBars(n - k, k); }          // xi >= 1
int starsBarsUpper(int n, int k, int u)                                  // 0 <= xi <= u (inclusion-exclusion)
{
    int res = 0;
    for (int j = 0; j <= k && j * (u + 1) <= n; j++)
    {
        int term = ncr(k, j) * starsBars(n - j * (u + 1), k) % MOD;
        res = (j & 1) ? (res - term + MOD) % MOD : (res + term) % MOD;
    }
    return res;
}

// ---- lattice paths, Catalan ----
int paths(int dx, int dy) { return (dx < 0 || dy < 0) ? 0 : ncr(dx + dy, dx); } // right dx, up dy
int catalan(int n) { return (ncr(2 * n, n) - ncr(2 * n, n + 1) + MOD) % MOD; }
int dyckFrom(int k, int b)                                               // k steps of +-1 from height b to 0, never below 0
{                                                                        // = completions of a bracket prefix with balance b
    if (b < 0 || b > k || (k + b) % 2) return 0;
    int d = (k + b) / 2;
    return (ncr(k, d) - ncr(k, d + 1) + MOD) % MOD;
}
int gridPathsBlocked(int h, int w, vpi blocked)                          // (1,1) -> (h,w) right/down, avoid blocked; O(k^2)
{
    sort(all(blocked));
    blocked.pb({h, w});
    int k = blocked.size();
    vi f(k);
    rep(i, 0, k)
    {
        f[i] = paths(blocked[i].first - 1, blocked[i].second - 1);
        rep(j, 0, i) if (blocked[j].second <= blocked[i].second)
            f[i] = (f[i] - f[j] * paths(blocked[i].first - blocked[j].first, blocked[i].second - blocked[j].second) % MOD + MOD) % MOD;
    }
    return f[k - 1];
}

// ---- inclusion-exclusion families ----
vi derangements(int n)                                                   // D[0..n]
{
    vi D(max(n + 1, 2LL));
    D[0] = 1, D[1] = 0;
    rep(i, 2, n + 1) D[i] = (i - 1) % MOD * ((D[i - 1] + D[i - 2]) % MOD) % MOD;
    return D;
}
int surjections(int n, int k)                                            // onto maps n -> k = k! * S2(n, k), O(k log n)
{
    int res = 0;
    rep(j, 0, k + 1)
    {
        int term = ncr(k, j) * binExp(k - j, n) % MOD;
        res = (j & 1) ? (res - term + MOD) % MOD : (res + term) % MOD;
    }
    return res;
}
int stirling2(int n, int k) { return (k < 0 || k > n) ? 0 : surjections(n, k) * invFact[k] % MOD; } // single value
int countDivisibleByAny(int n, const vi &d)                              // #x in [1, n] divisible by some d[i]; |d| <= ~20, exact
{
    int k = d.size(), total = 0;
    rep(mask, 1, 1LL << k)
    {
        int l = 1;
        rep(i, 0, k) if (mask >> i & 1)
        {
            l /= __gcd(l, d[i]);
            if (l > n / d[i]) { l = n + 1; break; }                      // lcm too large: term is 0
            l *= d[i];
        }
        total += (__builtin_popcountll(mask) & 1 ? 1 : -1) * (n / l);
    }
    return total;
}

// ---- Stirling, Bell, partitions (O(n^2) tables) ----
vvi stirling2Table(int n)                                                // S[i][j]: i labelled items into j unlabelled non-empty blocks
{
    vvi S(n + 1, vi(n + 1, 0));
    S[0][0] = 1;
    rep(i, 1, n + 1) rep(j, 1, i + 1) S[i][j] = (j * S[i - 1][j] + S[i - 1][j - 1]) % MOD;
    return S;
}
vvi stirling1Table(int n)                                                // c[i][j]: permutations of i with j cycles (unsigned)
{
    vvi S(n + 1, vi(n + 1, 0));
    S[0][0] = 1;
    rep(i, 1, n + 1) rep(j, 1, i + 1) S[i][j] = ((i - 1) * S[i - 1][j] + S[i - 1][j - 1]) % MOD;
    return S;
}
vi bell(int n)                                                           // B[0..n] via Bell triangle, O(n^2)
{
    vi B(n + 1), row(1, 1);
    B[0] = 1;
    rep(i, 1, n + 1)
    {
        vi nr(i + 1);
        nr[0] = row[i - 1];
        rep(j, 1, i + 1) nr[j] = (nr[j - 1] + row[j - 1]) % MOD;
        B[i] = nr[0];
        row = nr;
    }
    return B;
}
vi partitions(int n)                                                     // p[0..n], order of parts ignored
{
    vi p(n + 1, 0);
    p[0] = 1;
    rep(part, 1, n + 1) rep(s, part, n + 1) p[s] = (p[s] + p[s - part]) % MOD;
    return p;
}
vvi partitionsExactK(int n)                                              // q[k][s]: partitions of s into exactly k parts
{                                                                        // (into at most k parts = q[k][s + k])
    vvi q(n + 1, vi(n + 1, 0));
    q[0][0] = 1;
    rep(k, 1, n + 1) rep(s, k, n + 1) q[k][s] = (q[k - 1][s - 1] + q[k][s - k]) % MOD;
    return q;
}

// ---- permutations ----
vi inversionCounts(int n, int K)                                         // dp[k] = #perms of n with k inversions, O(nK)
{
    vi dp(K + 1, 0);
    dp[0] = 1;
    rep(i, 1, n + 1)
    {
        vi pre(K + 2, 0), nd(K + 1);
        rep(k, 0, K + 1) pre[k + 1] = (pre[k] + dp[k]) % MOD;
        rep(k, 0, K + 1) nd[k] = (pre[k + 1] - pre[max(0LL, k - i + 1)] + MOD) % MOD;
        dp = nd;
    }
    return dp;
}
int countCycles(const vi &p)                                             // p is a 0-indexed permutation
{
    int n = p.size(), c = 0;
    vector<bool> seen(n, false);
    rep(i, 0, n) if (!seen[i]) { c++; for (int j = i; !seen[j]; j = p[j]) seen[j] = true; }
    return c;
}

// ---- Burnside ----
int phiOf(int n)                                                         // Euler phi, O(sqrt n)
{
    int r = n;
    for (int p = 2; p * p <= n; p++) if (n % p == 0) { while (n % p == 0) n /= p; r -= r / p; }
    if (n > 1) r -= r / n;
    return r;
}
int necklaces(int n, int k)                                              // k colours, rotations equal; n up to 1e12
{
    int s = 0;
    for (int d = 1; d * d <= n; d++) if (n % d == 0)
    {
        s = (s + phiOf(n / d) % MOD * binExp(k, d)) % MOD;
        if (d * d != n) s = (s + phiOf(d) % MOD * binExp(k, n / d)) % MOD;
    }
    return s * modInv(n) % MOD;
}
int bracelets(int n, int k)                                              // rotations + reflections equal
{
    int refl = (n & 1) ? n % MOD * binExp(k, (n + 1) / 2) % MOD
                       : (n / 2) % MOD * ((binExp(k, n / 2 + 1) + binExp(k, n / 2)) % MOD) % MOD;
    int rot = necklaces(n, k) * (n % MOD) % MOD;
    return (rot + refl) % MOD * modInv(2 * n) % MOD;
}

// ---- trees (vertices 0..n-1) ----
int cayley(int n) { return n <= 2 ? 1 : binExp(n, n - 2); }             // labelled trees
int forests(int n, int k) { return k == n ? 1 : k % MOD * binExp(n, n - k - 1) % MOD; } // k trees, vertices 0..k-1 in different trees
int treesWithDegrees(const vi &deg)                                      // (n-2)! / prod (d_i - 1)!
{
    int n = deg.size(), s = 0, res = fact[max(0LL, n - 2)];
    if (n == 1) return deg[0] == 0;
    for (int d : deg) { if (d < 1) return 0; s += d - 1; res = res * invFact[d - 1] % MOD; }
    return s == n - 2 ? res : 0;
}
vpi pruferDecode(const vi &code)                                         // code length n-2 -> n-1 edges, O(n)
{
    int n = code.size() + 2, ptr = 0;
    vi deg(n, 1);
    for (int x : code) deg[x]++;
    while (deg[ptr] != 1) ptr++;
    int leaf = ptr;
    vpi edges;
    for (int v : code)
    {
        edges.pb({leaf, v});
        if (--deg[v] == 1 && v < ptr) leaf = v;
        else { ptr++; while (deg[ptr] != 1) ptr++; leaf = ptr; }
    }
    edges.pb({leaf, n - 1});
    return edges;
}
vi pruferEncode(int n, const vpi &edges)                                 // tree -> code of length n-2, O(n)
{
    vvi adj(n);
    for (auto &e : edges) adj[e.first].pb(e.second), adj[e.second].pb(e.first);
    vi par(n, -1), st(1, n - 1);
    par[n - 1] = n - 1;
    while (!st.empty())
    {
        int u = st.back(); st.pop_back();
        for (int v : adj[u]) if (par[v] == -1) par[v] = u, st.pb(v);
    }
    vi deg(n), code;
    rep(i, 0, n) deg[i] = adj[i].size();
    int ptr = 0;
    while (ptr < n && deg[ptr] != 1) ptr++;
    int leaf = ptr;
    rep(i, 0, n - 2)
    {
        int nxt = par[leaf];
        code.pb(nxt);
        if (--deg[nxt] == 1 && nxt < ptr) leaf = nxt;
        else { ptr++; while (deg[ptr] != 1) ptr++; leaf = ptr; }
    }
    return code;
}

// ---- number theory for counting ----
vi mobius(int n)                                                         // mu[0..n], linear sieve
{
    vi mu(n + 1, 0), primes;
    vector<bool> comp(n + 1, false);
    if (n >= 1) mu[1] = 1;
    rep(i, 2, n + 1)
    {
        if (!comp[i]) primes.pb(i), mu[i] = -1;
        for (int p : primes)
        {
            if (i * p > n) break;
            comp[i * p] = true;
            if (i % p == 0) { mu[i * p] = 0; break; }
            mu[i * p] = -mu[i];
        }
    }
    return mu;
}

// ---- polynomials / generating functions ----
void ntt(vi &a, bool invert)                                             // MOD must be 998244353 (primitive root 3)
{
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1)
    {
        int w = binExp(3, (MOD - 1) / len);
        if (invert) w = binExp(w, MOD - 2);
        for (int i = 0; i < n; i += len)
        {
            int wn = 1;
            rep(j, 0, len / 2)
            {
                int u = a[i + j], v = a[i + j + len / 2] * wn % MOD;
                a[i + j] = u + v < MOD ? u + v : u + v - MOD;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + MOD;
                wn = wn * w % MOD;
            }
        }
    }
    if (invert) { int ni = binExp(n, MOD - 2); for (int &x : a) x = x * ni % MOD; }
}
vi multiply(vi a, vi b)                                                  // polynomial product; naive if small or MOD != 998244353
{
    if (a.empty() || b.empty()) return vi();
    int need = a.size() + b.size() - 1;
    if (min(a.size(), b.size()) <= 32 || MOD != 998244353)
    {
        vi c(need, 0);
        rep(i, 0, (int)a.size()) rep(j, 0, (int)b.size()) c[i + j] = (c[i + j] + a[i] * b[j]) % MOD;
        return c;
    }
    int sz = 1;
    while (sz < need) sz <<= 1;
    a.resize(sz), b.resize(sz);
    ntt(a, false), ntt(b, false);
    rep(i, 0, sz) a[i] = a[i] * b[i] % MOD;
    ntt(a, true);
    a.resize(need);
    return a;
}

// ================ Sieve ================
int spf[N];
bool isPrime[N];
vector<vpi> distinct_primes(N);
vpi factorize(int x);
void sieve()
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
vpi factorize(int x)
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
// Example: every combinatorics helper once. Expected output is in the comment on each line.
void solve()
{
    // basics
    cout << ncr(5, 2) << ' ' << npr(5, 2) << ' ' << multinomial({3, 2, 1}) << nl;  // 10 20 60 (BANANA)
    cout << invNum(2) << ' ' << modInv(3) * 3 % MOD << nl;                           // 499122177 1
    cout << ncrBig(1000000000000000000LL, 2) << nl;                                   // C(1e18, 2) mod p
    auto C = pascal(10, 1000);                                                       // any modulus, even composite
    cout << C[10][5] << nl;                                                          // 252
    Lucas L3(3);
    cout << L3.C(7, 4) << ' ' << L3.C(10, 3) << nl;                                  // 2 0

    // stars and bars
    cout << starsBars(4, 3) << ' ' << starsBarsPos(4, 3) << ' ' << starsBarsUpper(10, 3, 4) << nl; // 15 3 6

    // lattice paths and Catalan
    cout << paths(2, 2) << ' ' << catalan(3) << ' ' << dyckFrom(4, 2) << nl;         // 6 5 3
    cout << gridPathsBlocked(5, 5, {{3, 3}}) << nl;                                  // 70 - 36 = 34

    // inclusion-exclusion
    vi D = derangements(6);
    cout << D[4] << ' ' << D[6] << nl;                                               // 9 265
    cout << surjections(5, 3) << ' ' << stirling2(5, 3) << nl;                       // 150 25
    cout << countDivisibleByAny(30, {2, 3, 5}) << nl;                                // 22

    // Stirling, Bell, partitions
    vvi S2 = stirling2Table(5), S1 = stirling1Table(4);
    cout << S2[4][2] << ' ' << S1[4][2] << nl;                                       // 7 11
    debug(bell(6));                                                                  // {1, 1, 2, 5, 15, 52, 203}
    vi p = partitions(10);
    vvi q = partitionsExactK(10);
    cout << p[10] << ' ' << q[2][4] << ' ' << q[2][4 + 2] << nl;                     // 42 2 3 (exactly 2 parts, at most 2 parts)

    // permutations
    debug(inversionCounts(4, 6));                                                    // {1, 3, 5, 6, 5, 3, 1}
    cout << countCycles({1, 2, 0, 4, 3}) << nl;                                      // 2: (0 1 2)(3 4)

    // Burnside
    cout << necklaces(4, 2) << ' ' << necklaces(6, 3) << ' ' << bracelets(6, 3) << nl; // 6 130 92

    // trees
    cout << cayley(4) << ' ' << forests(4, 2) << ' ' << treesWithDegrees({2, 2, 1, 1}) << nl; // 16 8 2
    vi code = {3, 3, 1};                                                             // n = 5
    vpi edges = pruferDecode(code);
    debug(edges, pruferEncode(5, edges));                                            // round trip gives {3, 3, 1}

    // Mobius: coprime ordered pairs in [1, 10]^2 = sum mu(d) * (10/d)^2
    vi mu = mobius(10);
    int cop = 0;
    rep(d, 1, 11) cop += mu[d] * (10 / d) * (10 / d);
    cout << cop << nl;                                                               // 63

    // generating functions: coins {1,2} -> (1+x+x^2+x^3)(1+x^2) up to x^3
    vi gf = multiply({1, 1, 1, 1}, {1, 0, 1, 0});
    cout << gf[3] << nl;                                                             // 2 ways to make 3

    // Mint for probabilities: expected inversions of a random permutation of 3 = 3/2
    Mint e = Mint(3) * Mint(2) / Mint(4);
    cout << e << ' ' << Mint(3, 2) << nl;                                            // 499122178 499122178
}

signed main()
{
    fast;
    // sieve();
    compute_factorials();
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
}
