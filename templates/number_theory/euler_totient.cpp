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


// ================ Euler Totient ================
// Uses: int(=ll), vi, rep, pb, all, MOD, Mint, umap. __int128 needs GCC/Clang.
// Don't paste together with the Mobius section (both define phi / primes).

vector<int32_t> phi; // phi[i], i <= LIM (int32_t to save memory)
vi Phi, primes;      // Phi[i] = phi[1] + ... + phi[i]
void phi_sieve(int LIM) // linear sieve, O(LIM). LIM = 1e7 uses ~130 MB
{
    phi.assign(LIM + 1, 0), Phi.assign(LIM + 1, 0), primes.clear();
    vector<bool> comp(LIM + 1, false);
    if (LIM >= 1) phi[1] = 1;
    rep(i, 2, LIM + 1)
    {
        if (!comp[i]) primes.pb(i), phi[i] = i - 1;
        for (int p : primes)
        {
            if (i * p > LIM) break;
            comp[i * p] = true;
            if (i % p == 0) { phi[i * p] = phi[i] * p; break; } // p already in i
            phi[i * p] = phi[i] * (p - 1);                      // p is new
        }
    }
    rep(i, 1, LIM + 1) Phi[i] = Phi[i - 1] + phi[i];
}

int phi_single(int n) // one n up to ~1e12, O(sqrt n)
{
    int res = n;
    for (int p = 2; p * p <= n; p++)
        if (n % p == 0)
        {
            while (n % p == 0) n /= p;
            res -= res / p;
        }
    if (n > 1) res -= res / n;
    return res;
}

vi phi_segment(int L, int R) // phi(x) for x in [L, R], R up to 1e12, R-L ~ 1e6. needs phi_sieve(>= sqrt R)
{
    int len = R - L + 1;
    vi rem(len), res(len);
    rep(i, 0, len) rem[i] = res[i] = L + i;
    for (int p : primes)
    {
        if (p * p > R) break;
        for (int x = (L + p - 1) / p * p; x <= R; x += p)
        {
            int i = x - L;
            res[i] -= res[i] / p;
            while (rem[i] % p == 0) rem[i] /= p;
        }
    }
    rep(i, 0, len) if (rem[i] > 1) res[i] -= res[i] / rem[i]; // one big prime left
    return res;
}

// ---- Euler's theorem ----
int power128(int a, int e, int m) // a^e mod m, m up to ~1e18
{
    int r = 1 % m;
    a %= m; if (a < 0) a += m;
    while (e > 0)
    {
        if (e & 1) r = (__int128)r * a % m;
        a = (__int128)a * a % m;
        e >>= 1;
    }
    return r;
}
int inv_mod_phi(int a, int m) { return power128(a, phi_single(m) - 1, m); } // needs gcd(a, m) = 1, m any

int str_mod(const string &s, int m)
{
    int r = 0;
    for (char c : s) r = ((__int128)r * 10 + (c - '0')) % m;
    return r;
}
int pow_huge(int a, const string &b, int m) // a^b mod m, b = huge decimal string, any a, m
{
    if (b.size() <= 2) return power128(a, stoll(b), m);
    int ph = phi_single(m);
    return power128(a, str_mod(b, ph) + ph, m); // extended Euler
}

int MODc(__int128 x, int m) { return x < m ? (int)x : (int)(x % m) + m; } // keeps "was it >= m"
int power_m(int a, int e, int m)
{
    int r = 1;
    while (e > 0)
    {
        if (e & 1) r = MODc((__int128)r * a, m);
        a = MODc((__int128)a * a, m);
        e >>= 1;
    }
    return r;
}
// a[i]^(a[i+1]^(...)), all a >= 1. final answer = tower(a, 0, m) % m
int tower(const vi &a, int i, int m)
{
    if (m == 1 || a[i] == 1 || i + 1 == (int)a.size()) return MODc(a[i], m);
    return power_m(a[i], tower(a, i + 1, phi_single(m)), m);
}

int primitive_root(int p) // p prime, smallest generator
{
    int ph = p - 1, n = ph;
    vi fac;
    for (int q = 2; q * q <= n; q++)
        if (n % q == 0) { fac.pb(q); while (n % q == 0) n /= q; }
    if (n > 1) fac.pb(n);
    for (int g = 2; g < p; g++)
    {
        bool ok = true;
        for (int q : fac) if (power128(g, ph / q, p) == 1) { ok = false; break; }
        if (ok) return g;
    }
    return 1; // p = 2
}

// ---- gcd / lcm sums ----
vi pillai, lcmG; // pillai[n] = sum_{i<=n} gcd(i, n), lcmG[n] = sum_{d|n} d*phi(d)
void build_gcd_lcm_sums(int n) // O(n log n), needs phi_sieve(n)
{
    pillai.assign(n + 1, 0), lcmG.assign(n + 1, 0);
    rep(d, 1, n + 1) for (int m = d; m <= n; m += d)
        pillai[m] += d * phi[m / d], lcmG[m] += d * phi[d];
}
int lcm_sum(int n) { return n * (lcmG[n] + 1) / 2; } // sum_{i<=n} lcm(i, n), exact for n <= 1e6

template <class F> int sum_f_gcd(int n, F f) // sum_{k=1..n} f(gcd(k, n)) for one n
{
    int res = 0;
    for (int d = 1; d * d <= n; d++)
        if (n % d == 0)
        {
            res += f(d) * phi_single(n / d);
            if (d != n / d) res += f(n / d) * phi_single(d);
        }
    return res;
}

int sum_gcd_rect(int n, int m) // sum_{i<=n, j<=m} gcd(i, j), O(sqrt), needs phi_sieve(>= min(n, m))
{
    int ans = 0;
    for (int l = 1, r, lim = min(n, m); l <= lim; l = r + 1)
    {
        r = min(n / (n / l), m / (m / l));
        ans += (Phi[r] - Phi[l - 1]) * (n / l) * (m / l);
    }
    return ans;
}
int sum_gcd_i_lt_j(int n) { return (sum_gcd_rect(n, n) - n * (n + 1) / 2) / 2; } // sum over i < j

// ---- coprime counting (square [1, n]^2 only; for rectangles use Mobius) ----
int coprime_pairs_square(int n) { return n ? 2 * Phi[n] - 1 : 0; } // ordered (a, b)
int pairs_gcd_exact(int n, int g) { return coprime_pairs_square(n / g); }
int pairs_gcd_prime(int n)
{
    int ans = 0;
    for (int p : primes) { if (p > n) break; ans += coprime_pairs_square(n / p); }
    return ans;
}

int count_coprime(int X, int n) // #x in [1, X] with gcd(x, n) = 1
{
    vi ps;
    for (int p = 2; p * p <= n; p++)
        if (n % p == 0) { ps.pb(p); while (n % p == 0) n /= p; }
    if (n > 1) ps.pb(n);
    int k = ps.size(), res = 0;
    rep(mask, 0, 1LL << k)
    {
        int prod = 1, bits = 0;
        rep(i, 0, k) if (mask >> i & 1) prod *= ps[i], bits++;
        res += (bits & 1 ? -1 : 1) * (X / prod);
    }
    return res;
}
int kth_coprime(int k, int n) // k-th positive integer coprime to n
{
    int ph = phi_single(n), full = (k - 1) / ph, r = (k - 1) % ph + 1;
    int lo = 1, hi = n;
    while (lo < hi)
    {
        int mid = (lo + hi) / 2;
        if (count_coprime(mid, n) >= r) hi = mid; else lo = mid + 1;
    }
    return full * n + lo;
}

Mint sum_coprime(int n) // sum of k <= n with gcd(k, n) = 1, mod MOD
{
    if (n == 1) return 1;
    int ph = phi_single(n);
    return n % 2 == 0 ? Mint(n / 2) * Mint(ph) : Mint(n) * Mint(ph / 2);
}

Mint necklaces(int n, int k) // n beads, k colours, rotations count once. n < MOD
{
    Mint s = 0;
    for (int d = 1; d * d <= n; d++)
        if (n % d == 0)
        {
            s += Mint(phi_single(d)) * mexp(Mint(k), n / d);
            if (d != n / d) s += Mint(phi_single(n / d)) * mexp(Mint(k), d);
        }
    return s / Mint(n);
}

// ---- advanced ----
umap<int, Mint> memoPhi;
Mint tri_mod(int n) // n(n+1)/2 mod MOD
{
    int a = n, b = n + 1;
    if (a % 2 == 0) a /= 2; else b /= 2;
    return Mint(a % MOD) * Mint(b % MOD);
}
Mint Phi_du(int n) // (phi(1)+...+phi(n)) mod MOD, n up to ~1e11. needs phi_sieve(LIM ~ n^(2/3))
{
    if (n < (int)Phi.size()) return Mint(Phi[n] % MOD);
    auto it = memoPhi.find(n);
    if (it != memoPhi.end()) return it->second;
    Mint res = tri_mod(n);
    for (int l = 2, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        res -= Mint((r - l + 1) % MOD) * Phi_du(n / l);
    }
    return memoPhi[n] = res;
}

bool is_prime_slow(int x)
{
    if (x < 2) return false;
    for (int d = 2; d * d <= x; d++) if (x % d == 0) return false;
    return true;
}
vi invCand, invSols;
void dfs_inv(int i, int rem, int cur)
{
    if (rem == 1) invSols.pb(cur);
    rep(j, i, (int)invCand.size())
    {
        int p = invCand[j];
        if (rem % (p - 1) != 0) continue;
        int r = rem / (p - 1), c = cur * p;
        while (true)
        {
            dfs_inv(j + 1, r, c);
            if (r % p != 0) break;
            r /= p, c *= p;
        }
    }
}
vi inverse_phi(int k) // all n with phi(n) = k, sorted
{
    invCand.clear(), invSols.clear();
    for (int d = 1; d * d <= k; d++)
        if (k % d == 0)
        {
            if (is_prime_slow(d + 1)) invCand.pb(d + 1);
            if (d != k / d && is_prime_slow(k / d + 1)) invCand.pb(k / d + 1);
        }
    sort(all(invCand));
    dfs_inv(0, k, 1);
    sort(all(invSols));
    return invSols;
}

//================ Code starts here ================
// Demo of every totient function. Each line prints "got | expected".
// For a real problem, delete the demo and write your solution here.
void solve()
{
    // ---- computing phi ----
    cout << "phi[1..12] = "; rep(i, 1, 13) cout << phi[i] << " "; cout << "| 1 1 2 2 4 2 6 4 6 4 10 4" << nl;
    cout << "Phi[1e6] = " << Phi[1000000] << " | 303963552392" << nl;
    cout << "phi_single(360) = " << phi_single(360) << " | 96" << nl;
    cout << "phi_single(1e12) = " << phi_single(1000000000000LL) << " | 400000000000" << nl;
    vi seg = phi_segment(1000000000000LL - 4, 1000000000000LL);
    bool segOk = true;
    rep(i, 0, 5) segOk &= seg[i] == phi_single(1000000000000LL - 4 + i);
    cout << "phi_segment near 1e12 matches phi_single: " << (segOk ? "yes" : "NO") << " | yes" << nl;

    // ---- Euler's theorem ----
    cout << "inv_mod_phi(7, 12) = " << inv_mod_phi(7, 12) << " | 7" << nl;
    cout << "inv_mod_phi(5, 36) = " << inv_mod_phi(5, 36) << " | 29" << nl;
    cout << "pow_huge(2, \"100\", 15) = " << pow_huge(2, "100", 15) << " | 1" << nl;
    cout << "2^(10^21) mod 12 = " << pow_huge(2, "1" + string(21, '0'), 12) << " | 4" << nl;
    cout << "tower 2^3^4^5 mod 1e9+7 = " << tower({2, 3, 4, 5}, 0, 1000000007) % 1000000007 << " | 7513152" << nl;
    cout << "tower 2^2^2^2 mod 1000 = " << tower({2, 2, 2, 2}, 0, 1000) % 1000 << " | 536" << nl;
    cout << "primitive_root(998244353) = " << primitive_root(998244353) << " | 3" << nl;

    // ---- gcd / lcm sums ----
    build_gcd_lcm_sums(1000000);
    cout << "sum gcd(i,12) = " << pillai[12] << " | 40" << nl;
    cout << "sum_f_gcd(12, f(g)=g) = " << sum_f_gcd(12, [](int g) { return g; }) << " | 40" << nl;
    cout << "lcm_sum(12) = " << lcm_sum(12) << " | 468" << nl;
    cout << "lcm_sum(1e6) = " << lcm_sum(1000000) << " | 277811686426000000" << nl;
    cout << "sum_gcd_rect(6, 6) = " << sum_gcd_rect(6, 6) << " | 61" << nl;
    cout << "sum_gcd_i_lt_j(6) = " << sum_gcd_i_lt_j(6) << " | 20" << nl;
    cout << "sum_gcd_i_lt_j(1e6) = " << sum_gcd_i_lt_j(1000000) << " | 4071628673912" << nl;

    // ---- coprime counting ----
    cout << "coprime_pairs_square(6) = " << coprime_pairs_square(6) << " | 23" << nl;
    cout << "pairs_gcd_exact(10, 2) = " << pairs_gcd_exact(10, 2) << " | 19" << nl;
    cout << "pairs_gcd_prime(10) = " << pairs_gcd_prime(10) << " | 30" << nl;
    cout << "count_coprime(100, 12) = " << count_coprime(100, 12) << " | 33" << nl;
    cout << "kth_coprime(10, 12) = " << kth_coprime(10, 12) << " | 29" << nl;
    cout << "sum_coprime(12) = " << sum_coprime(12) << " | 24" << nl;
    cout << "necklaces(4, 2) = " << necklaces(4, 2) << " | 6" << nl;
    cout << "necklaces(6, 3) = " << necklaces(6, 3) << " | 130" << nl;

    // ---- advanced ----
    cout << "Phi_du(1e9) mod 998244353 = " << Phi_du(1000000000) << " | 422516288" << nl;
    cout << "Phi_du(1e10) mod 998244353 = " << Phi_du(10000000000LL) << " | 866849765" << nl;
    cout << "inverse_phi(8) = "; for (int x : inverse_phi(8)) cout << x << " "; cout << "| 15 16 20 24 30" << nl;
    cout << "#n with phi(n) = 5e8: " << inverse_phi(500000000).size() << " | 106" << nl;
}

signed main()
{
    fast;
    phi_sieve(2000000); // LIM = largest value you look up in phi / Phi (and ~n^(2/3) for Phi_du)
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
}
