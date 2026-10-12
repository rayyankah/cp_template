//hackerrank-->move the coins(hard)
const int maxN = 5e4 + 10;
vi adj[maxN];
vi levels(maxN, -1);
vi tin(maxN, 0), tout(maxN, 0);
int timer = 0;
int subtree_xor[maxN][2]; // 0->even, 1->odd
int parent[maxN];
vi coins(maxN, 0);
void dfs(int node, int par)
{
    parent[node] = par;
    levels[node] = (par == -1) ? 0 : levels[par] + 1;
    tin[node] = ++timer;
    subtree_xor[node][levels[node] % 2] ^= coins[node];
    for (auto &child : adj[node])
    {
        if (child != par)
        {
            dfs(child, node);
            subtree_xor[node][0] ^= subtree_xor[child][0];
            subtree_xor[node][1] ^= subtree_xor[child][1];
        }
    }
    tout[node] = ++timer;
}
//================ Code starts here ================
void solve()
{
    int n;
    cin >> n;

    
    rep(i, 1, n + 1)
    {
        adj[i].clear();
        levels[i] = -1;
        parent[i] = -1;
        subtree_xor[i][0] = 0;
        subtree_xor[i][1] = 0;
        tin[i] = 0;
        tout[i] = 0;
    }
    timer = 0;

    rep(i, 1, n + 1)
    {
        cin >> coins[i];
    }


    rep(i, 0, n - 1)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    dfs(1, -1);
    int xxor = 0;
    // staircase nim: xor of coin piles on odd-depth nodes
    rep(i, 1, n + 1)
    {
        if (levels[i] & 1)
        {
            xxor ^= coins[i];
        }
    }
    int q;
    cin >> q;
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        if ( (tin[u] <= tin[v] && tout[v] <= tout[u]))
        {
            cout << "INVALID" << nl;
            continue;
        }

        int dist = levels[v] + 1;
        if (((dist & 1) == (levels[u] & 1)))
        {
            if (xxor == 0)
            {
                cout << "NO" << nl;
            }
            else
            {
                cout << "YES" << nl;
            }
        }
        else
        {
            int newxor = xxor;
            newxor ^= subtree_xor[u][0];
            newxor ^= subtree_xor[u][1];
            if (newxor == 0)
            {
                cout << "NO" << nl;
            }
            else
            {
                cout << "YES" << nl;
            }
        }
    }
}
