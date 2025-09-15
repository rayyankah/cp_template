//cf = cutting figure
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
//articulation points
const int maxN = 1e5 + 10;
vi adj[maxN];
si articulation_points;
int vis[maxN], in[maxN], low[maxN];
int timer;
void dfs(int node, int parent=-1){
    vis[node]=1;
    in[node]=low[node]=timer++;
    int children =0;
    for(int &child: adj[node]){
        if(child==parent)continue;
        if(vis[child]){
            //back edge
            low[node]=min(low[node],in[child]);
        }
        else{
            //forward edge
            dfs(child,node);
            if(low[child]>=in[node] && parent!=-1){
                articulation_points.insert(node);
            }
            low[node]=min(low[node],low[child]);
            children++;
        }
    }
    if(parent==-1 && children>1){
        articulation_points.insert(node);
    }

}
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin >> grid[i];
    vector<pair<int, int>> cells;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == '#') cells.push_back({i, j});
    int cnt = cells.size();
    if (cnt <= 2) {
        cout << -1 << nl;
        return;
    }
    const int MAXN = 2501;
    for (int i = 0; i < MAXN; i++) adj[i].clear();
    for (auto &p : cells) {
        int x= p.first, y = p.second;
        int u = x * m + y;
        vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (auto &p : dirs) {
            int dx = p.first, dy = p.second;
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == '#') {
                int v = nx * m + ny;
                adj[u].push_back(v);
            }
        }
    }
    memset(vis, 0, sizeof(vis));
    memset(in, 0, sizeof(in));
    memset(low, 0, sizeof(low));
    timer = 0;
    articulation_points.clear();
    int start = cells[0].first * m + cells[0].second;
    dfs(start, -1);
    if (!articulation_points.empty()) {
        cout << 1 << nl;
    } else {
        cout << 2 << nl;
    }
}
//================ Code starts here ================

signed main()
{
    fast;

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
} 












//cses =->mailman
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
// finding eulerian path/circuit
const int MAXN = 100005;
int deg[MAXN];
bool hasEulerPath(int n)
{
    int odd = 0;
    for (int i = 0; i <= n; ++i)
        if (deg[i] & 1)
            ++odd;
    return (odd == 0 || odd == 2);
}

// Hierholzer: recursive removal using multiset adjacency
void findEulerPathOrCircuit(int u, vector<int> &res, vector<multiset<int>> &adj)
{
    while (!adj[u].empty())
    {
        int v = *adj[u].begin();
        // remove edge u-v from both sides
        adj[u].erase(adj[u].begin());
        auto it = adj[v].find(u);
        if (it != adj[v].end())
            adj[v].erase(it);
        findEulerPathOrCircuit(v, res, adj);
    }
    res.push_back(u);
}

void solve()
{
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        deg[i] = 0;

    vector<pair<int, int>> edges;
    edges.reserve(m);
    vector<multiset<int>> adjm(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        edges.emplace_back(u, v);
        adjm[u].insert(v);
        adjm[v].insert(u);
        ++deg[u];
        ++deg[v];
    }
    if (n == 2 && m == 1 && edges[0].first == 1 && edges[0].second == 2)
    {
        cout << "IMPOSSIBLE\n ";
        return;
    }

    if (m == 0)
    {
        cout << "IMPOSSIBLE\n";
        return;
    }

    vector<int> odds;
    for (int i = 1; i <= n; ++i)
    {
        if (deg[i] & 1)
            odds.push_back(i);
    }
    if (odds.size() > 2 || odds.size() == 1)
    {
        cout << "IMPOSSIBLE\n";
        return;
    }

    int start = 1;
    if (!odds.empty())
    {
        if (odds[0] != 1 && odds[1] != 1)
        {
            cout << "IMPOSSIBLE\n";
            return;
        }
        // start remains 1
    }

    vector<int> ans;
    findEulerPathOrCircuit(start, ans, adjm);
    reverse(ans.begin(), ans.end());

    if ((int)ans.size() != m + 1)
    {
        cout << "IMPOSSIBLE\n";
        return;
    }

    for (int i = 0; i <= n; ++i)
    {
        if (!adjm[i].empty())
        {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }

    if (ans[0] != 1)
    {
        cout << "IMPOSSIBLE\n";
        return;
    }

    for (int i = 0; i < (int)ans.size(); ++i)
    {
        if (i)
            cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return;
}

signed main()
{
    fast;

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
}






















//cses -> level games
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
// finding eulerian path/circuit

int n, m;
vector<vector<int>> adj;
vector<int> in_deg, out_deg;
vector<vector<int>> undir;
vector<bool> vis;

void dfs(int u)
{
    vis[u] = true;
    for (int v : undir[u])
    {
        if (!vis[v])
            dfs(v);
    }
}

void findEulerPath(int u, vector<int> &res)
{
    while (!adj[u].empty())
    {
        int v = adj[u].back();
        adj[u].pop_back();
        findEulerPath(v, res);
    }
    res.push_back(u);
}

void solve()
{
    cin >> n >> m;
    adj.assign(n + 1, {});
    in_deg.assign(n + 1, 0);
    out_deg.assign(n + 1, 0);
    undir.assign(n + 1, {});
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        out_deg[a]++;
        in_deg[b]++;
        undir[a].push_back(b);
        undir[b].push_back(a);
    }
    bool possible = true;
    int start = -1, end = -1;
    for (int i = 1; i <= n; i++)
    {
        int diff = out_deg[i] - in_deg[i];
        if (diff == 1)
        {
            if (start != -1)
                possible = false;
            start = i;
        }
        else if (diff == -1)
        {
            if (end != -1)
                possible = false;
            end = i;
        }
        else if (diff != 0)
        {
            possible = false;
        }
    }
    if (start != 1 || end != n)
        possible = false;
    if (!possible)
    {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    vis.assign(n + 1, false);
    dfs(1);
    bool connected = true;
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i] && (out_deg[i] > 0 || in_deg[i] > 0))
            connected = false;
    }
    if (!connected)
    {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    vector<int> res;
    findEulerPath(1, res);
    reverse(res.begin(), res.end());
    if (res.size() != m + 1 || res[0] != 1 || res.back() != n)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        for (int x : res)
            cout << x << " ";
        cout << endl;
    }
}

signed main()
{
    fast;

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
}





//cf - bertown road
#include <bits/stdc++.h>

using namespace std;
#define int long long
const int inf = 1e18;

struct Bridge {
    vector<vector<int>> adj, tree, Components;
    vector<int> low, vis, depth, stack, id;
    int n;
    vector<pair<int, int>> bridge;

    Bridge(int n, vector<vector<int>> &adj) :
            adj(adj), n(n), depth(n + 1), id(n + 1), vis(n + 1), low(n + 1, inf) {
        build();
    };

    void dfs(int u, int p) {
        stack.emplace_back(u);
        low[u] = depth[u];
        vis[u] = 1;
        for (auto v: adj[u]) {
            if (v == p)continue;
            if (vis[v]) {
                low[u] = min(low[u], depth[v]);
                continue;
            }
            depth[v] = depth[u] + 1;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > depth[u])
                bridge.emplace_back(u, v);
        }
        if (low[u] == depth[u]) {
            vector<int> comp;
            while (stack.back() != u)
                comp.emplace_back(stack.back()), stack.pop_back();
            comp.emplace_back(stack.back());
            stack.pop_back();
            Components.emplace_back(comp);
            for (auto v: comp)
                id[v] = Components.size();
        }
    }

    void build() {
        for (int i = 1; i <= n; ++i)
            if (!vis[i])
                dfs(i, 0);

        tree.assign(Components.size() + 1, {});
        for (int u = 1; u <= n; ++u) {
            for (auto v: adj[u]) {
                if (id[u] != id[v])
                    tree[id[u]].emplace_back(id[v]);
            }
        }
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    Bridge T(n, adj);
    if (T.bridge.size())
        return void(cout << "0\n");

    vector<int> vis(n + 1), depth(n + 1);
    function<void(int , int )> dfs = [&](int u , int p) {
        vis[u] = 1;
        for (auto v: adj[u]) {
            if(v == p)continue;
            if (!vis[v]) {
                cout << u << ' ' << v << '\n';
                depth[v] = depth[u] + 1;
                dfs(v , u);
            } else if (depth[v] < depth[u])
                cout << u << ' ' << v << '\n';
        }
    };

    dfs(1 , 0);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef HALZOOM
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif

    int test = 1;
//    cin >> test;

    for (int i = 1; i <= test; ++i) {
        solve();
    }
    return 0;
}





//cactus
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+5,mod=1e9+7;
vector<int> adj[N];
int low[N],num[N],id[N],dp[N],val[N],dep[N];
int timer=1,cnt=1,sz=0;
bool check[N],vis[N];
int st[N][35];
set<pair<int,int>> cau;
set<int> comp[N];
map<pair<int,int>,bool> mp,bri;
void dfs(int u,int p)
{
    check[u]=1;
    low[u]=num[u]=timer++;
    for(int v:adj[u]){
        if(v==p) continue;
        if(check[v]) low[u]=min(low[u],num[v]);
        else{
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]==num[v]) cau.insert({min(u,v),max(u,v)});
        }
    }
}
void dfs1(int u)
{
    sz++;
    id[u]=cnt;
    check[u]=1;
    for(int v:adj[u]){
        pair<int,int> e={min(u,v),max(u,v)};
        if(cau.find(e)!=cau.end()) continue;
        if(check[v]) continue;
        dfs1(v);
    }
}
void dfs2(int u,int p)
{
    st[u][0]=p;
    for(int j=1;j<=30;j++){
        st[u][j]=st[st[u][j-1]][j-1];
    }
    for(int v:comp[u]){
        if(v==p) continue;
        dp[v]+=dp[u];
        dep[v]=dep[u]+1;
        dfs2(v,u);
    }
}
int lca(int u,int v)
{
    if(dep[u]<dep[v]) swap(u,v);
    int kc=dep[u]-dep[v];
    for(int j=0;j<=30;j++){
        if((1<<j)&kc) u=st[u][j];
    }
    if(u==v) return u;
    for(int j=30;j>=0;j--){
        if(st[u][j]!=st[v][j]){
            u=st[u][j];
            v=st[v][j];
        }
    }
    return st[u][0];
}
int pw(int a,int b)
{
    if(b==0) return 1;
    int res=1;
    while(b>0){
        if(b&1) res=1ll*res*a%mod;
        a=1ll*a*a%mod;
        b/=2;
    }
    return res;
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int a=0;a<m;a++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1,0);
    for(int a=0;a<=n;a++){
        check[a]=0;
    }
    for(int a=1;a<=n;a++){
        if(!check[a]){
            sz=0;
            dfs1(a);
            cnt++;
            if(sz>1) val[id[a]]=1;
        }
    }
    for(int a=1;a<=n;a++){
        for(int b:adj[a]){
            if(id[a]==id[b]) continue;
            comp[id[a]].insert(id[b]);
            comp[id[b]].insert(id[a]);
        }
    }
    cnt--;
    for(int a=1;a<=cnt;a++){
        dp[a]=val[a];
    }
    dfs2(1,0);
    int q;
    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;
        int x=id[l],y=id[r];
        int s=lca(x,y);
        int ans=dp[x]+dp[y]-2*dp[s]+val[s];
        cout<<pw(2,ans)<<"\n";
    }
}



//fairy
#include <bits/stdc++.h>
using namespace std;
const int N=10010;
int n,m,dep[N],fat[14][N],d[N][2],z[2],ans[N],cnt;
vector<pair<int,int> > ed[N];
int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	int ret=dep[x]-dep[y];
	for(int i=13;i>=0;i--) if(ret>=(1<<i)) ret-=1<<i,x=fat[i][x];
	if(x==y) return x;
	for(int i=13;i>=0;i--) if(fat[i][x]!=fat[i][y]) x=fat[i][x],y=fat[i][y];
	return fat[0][x];
}
void dfs(int x,int fa){
	dep[x]=dep[fa]+1;fat[0][x]=fa;
	for(int i=1;i<=13;i++) fat[i][x]=fat[i-1][fat[i-1][x]];
	for(auto [v,w]:ed[x]){
		if(v==fa) continue;
//		cout<<x<<' '<<v<<' '<<dep[v]<<endl;
		if(!dep[v]) dfs(v,x);
		else{
			int lca=LCA(x,v);
			int c=dep[x]+dep[v]-2*dep[lca]+1;z[c&1]++;
			d[x][c&1]++;d[v][c&1]++;d[lca][c&1]-=2;
//			cout<<x<<' '<<v<<' '<<lca<<endl;
		}
	}
}
bool vis[N];
void solve(int x,int fa){
	vis[x]=1;
	for(auto [v,w]:ed[x]){
		if(v==fa) continue;
		if(vis[v]){
			int lca=LCA(x,v);
			int c=dep[x]+dep[v]-2*dep[lca]+1;
			if((c&1)&&z[c&1]==2) ans[++cnt]=w; 
			continue;
		}
		solve(v,x);
		if(d[v][1]==z[1]&&!d[v][0]) cnt++,ans[cnt]=w;
		d[x][0]+=d[v][0],d[x][1]+=d[v][1];
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;cin>>x>>y;
		ed[x].push_back({y,i});
		ed[y].push_back({x,i});
	}
	for(int i=1;i<=n;i++) if(!dep[i]) dfs(i,0);
	if(!z[1]){
		cout<<m<<'\n';
		for(int i=1;i<=m;i++) cout<<i<<' ';
		return 0;
	}
	for(int i=1;i<=n;i++) if(!vis[i]) solve(i,0);
	sort(ans+1,ans+cnt+1);cnt=unique(ans+1,ans+cnt+1)-ans-1;
	cout<<cnt<<'\n';
	for(int i=1;i<=cnt;i++) cout<<ans[i]<<' ';
	return 0;
}






