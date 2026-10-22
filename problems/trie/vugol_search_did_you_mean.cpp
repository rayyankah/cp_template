// Vugol Search ("Did you mean...") - ICPC Dhaka Regional Preliminary 2018, Problem I
// N database words, each with a smartness value. For a query word A, the score of database word B is
//   LCP(A,B) + IsAnagram(A,B) * smartness(B)
// For each of Q queries print the maximum score over all database words.
// Approach: one global trie gives max LCP; words are also grouped by sorted-letters (anagram class),
// each class has its own trie storing the max smartness in every subtree. Query answer =
// max(global LCP, best (LCP-depth + subtree smartness) along the query path in its anagram-class trie).

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
const int MOD = 998244353;
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
struct Mint
{
    int value;
    static const int MOD_value = MOD;

    Mint(long long v = 0)
    {
        value = v % MOD;
        if (value < 0)
            value += MOD;
    }
    Mint(long long a, long long b) : value(0)
    {
        *this += a;
        *this /= b;
    }

    Mint &operator+=(Mint const &b)
    {
        value += b.value;
        if (value >= MOD)
            value -= MOD;
        return *this;
    }
    Mint &operator-=(Mint const &b)
    {
        value -= b.value;
        if (value < 0)
            value += MOD;
        return *this;
    }
    Mint &operator*=(Mint const &b)
    {
        value = (long long)value * b.value % MOD;
        return *this;
    }

    friend Mint mexp(Mint a, long long e)
    {
        Mint res = 1;
        while (e)
        {
            if (e & 1)
                res *= a;
            a *= a;
            e >>= 1;
        }
        return res;
    }
    friend Mint inverse(Mint a) { return mexp(a, MOD - 2); }

    Mint &operator/=(Mint const &b) { return *this *= inverse(b); }
    friend Mint operator+(Mint a, Mint const b) { return a += b; }
    friend Mint operator-(Mint a, Mint const b) { return a -= b; }
    friend Mint operator-(Mint const a) { return 0 - a; }
    friend Mint operator*(Mint a, Mint const b) { return a *= b; }
    friend bool operator<(Mint const &a, Mint const &b) { return a.value < b.value; }
    friend Mint operator/(Mint a, Mint const b) { return a /= b; }
    friend std::ostream &operator<<(std::ostream &os, Mint const &a) { return os << a.value; }
    friend bool operator==(Mint const &a, Mint const &b) { return a.value == b.value; }
    friend bool operator!=(Mint const &a, Mint const &b) { return a.value != b.value; }
};
vector<vpi> distinct_primes(N);
vi spf(N);
int isPrime[N];
void sieve()
{
    rep(i, 2, N)
    {
        if (spf[i] == 0)
        {
            spf[i] = i;
            isPrime[i] = 1;
            for (int j = i * 2; j < N; j += i)
            {
                if (spf[j] == 0)
                {
                    spf[j] = i;
                }
            }
        }
    }
    rep(i, 2, N)
    {
        int x = i;
        while (x > 1)
        {
            int p = spf[x];
            int cnt = 0;
            while (x % p == 0)
            {
                x /= p;
                cnt++;
            }
            distinct_primes[i].pb({p, cnt});
        }
    }
}

// implementing trie
const int SIZE = 26;
struct TrieNode
{
    int count;
    int smartness;
    bool endOfWord;
    TrieNode *children[SIZE];
    TrieNode(int smart = 0)
    {
        count = 0;
        endOfWord = false;
        smartness = smart;
        for (int i = 0; i < SIZE; i++)
        {
            children[i] = nullptr;
        }
    }
};
class Trie
{
public:
    TrieNode *root;

public:
    Trie()
    {
        root = new TrieNode();
    }
    void insert(string word, int smart = 0)
    {
        TrieNode *temp = root;
        for (char c : word)
        {
            int idx = c - 'a';
            if (temp->children[idx] == nullptr)
            {
                // ekhono banano hy ni, so new node create
                temp->children[idx] = new TrieNode(smart);
            }
            temp = temp->children[idx];
            temp->smartness = max<ll>(temp->smartness, smart);
            temp->count++;
        }
        temp->endOfWord = true;
    }
    void calcSmart(TrieNode *root)
    {
        if (root == nullptr)
            return;
        TrieNode *temp = root;
        int mx = temp->smartness;
        rep(i, 0, 26)
        {
            if (temp->children[i] != nullptr)
            {
                calcSmart(temp->children[i]);
                mx = max<ll>(mx, temp->children[i]->smartness);
            }
        }
        temp->smartness = mx;
    }
    pi search(string word)
    {
        int cnt = 0;

        TrieNode *temp = root;
        int mx = temp->smartness;
        for (char c : word)
        {
            int idx = c - 'a';
            if (temp->children[idx] == nullptr)
            {
                return {cnt, mx};
            }
            cnt++;
            temp = temp->children[idx];
            mx = max<ll>(mx, cnt + temp->smartness);
        }
        return {cnt, mx};
    }
    bool startsWith(string prefix)
    {
        TrieNode *temp = root;
        for (char c : prefix)
        {
            int idx = c - 'a';
            if (temp->children[idx] == nullptr)
            {
                return false;
            }
            temp = temp->children[idx];
        }
        return true;
    }
    int countWordsStartingWith(string prefix)
    {
        TrieNode *temp = root;
        for (char c : prefix)
        {
            int idx = c - 'a';
            if (temp->children[idx] == nullptr)
            {
                return 0;
            }
            temp = temp->children[idx];
        }
        return temp->count;
    }
};
// usage: Trie t; t.insert(s); t.search(s); t.countWordsStartingWith(p); t.erase(s). lowercase only

//================ Code starts here ================
void solve()
{
    int n;
    cin >> n;
    vi a(n);
    read(a);
    vector<string> ss(n);
    rep(i, 0, n)
    {
        cin >> ss[i];
    }
    Trie *mainn = new Trie();
    rep(i, 0, n)
    {
        mainn->insert(ss[i]);
    }
    vector<string> temp = ss;
    rep(i, 0, n)
    {
        sort(all(temp[i]));
    }
    map<string, int> idd;
    map<int, Trie *> kontrie;
    int nowid = -1;
    rep(i, 0, n)
    {
        if (idd.find(temp[i]) == idd.end())
        {
            idd[temp[i]] = ++nowid;
            kontrie[nowid] = new Trie();
        }
        kontrie[idd[temp[i]]]->insert(ss[i],a[i]);
    }
    for(auto &ele: kontrie){
        ele.second->calcSmart(ele.second->root);
    }

    int q;
    cin >> q;
    while (q--)
    {
        string a;
        cin >> a;
        int lc = mainn->search(a).first;
        int sec = 0;
        string tem = a;
        sort(all(tem));
        if (idd.find(tem) != idd.end())
        {
            sec = kontrie[idd[tem]]->search(a).second;
        }
        cout << max<ll>(sec, lc) << nl;
    }
}

signed main()
{
    fast;
    // sieve();
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
}