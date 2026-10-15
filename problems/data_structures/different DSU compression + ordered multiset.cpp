// https://codeforces.com/gym/724491/problem/E
// The Social Network (ICPC Dhaka Regional Preliminary 2019, Problem B)
// DSU small-to-large merge (by post count) + ordered set of {time, id} as multiset

template <class T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int sz[N];
int parent[N];
ordered_set<pi> ss[N];
void make(int n)
{
    parent[n] = n;
    sz[n] = 1;
}
int find(int v)
{
    if (parent[v] == v)
        return v;
    return parent[v] = find(parent[v]);
}
void Union(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a != b)
    {
        if (ss[a].size() < ss[b].size())
        {

            swap(a, b);
        }
        parent[b] = a;
        sz[a] += sz[b];
        sz[b] = 0;
        for (auto &ele : ss[b])
        {
            ss[a].insert(ele);
        }
        ss[b].clear();
    }
}

//================ Code starts here ================
void solve(int tc)
{
    int n, q;
    cin >> n >> q;
    rep(i, 1, n + 1)
    {
        make(i);
    }
    cout << "Case " << tc << ":" << nl;
    int id = 0;
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 0)
        {
            int a, b;
            cin >> a >> b;
            Union(a, b);
        }
        else if (type == 1)
        {
            int a, time;
            cin >> a >> time;
            ss[find(a)].insert({time, id++});
            // if (tc == 2)
            //     debug(a, ss[find(a)]);
        }
        else
        {
            int a, l, r;
            cin >> a >> l >> r;
            int hi = ss[find(a)].order_of_key({r + 1, INT_MIN});
            // ss[1].insert(10);
            // if (tc == 2)

            // debug(ss[1]);
            // debug(ss[find(a)]);
            int lo = 0;
            if (l > 0)
                lo = ss[find(a)].order_of_key({l, INT_MIN});
            cout << hi - lo << nl;
        }
    }
    rep(i, 1, n + 1)
    {
        ss[i].clear();
    }
}

signed main()
{
    fast;
    // preprocessing();
    int t = 1;
    cin >> t;
    rep(i, 1, t + 1) solve(i);
}