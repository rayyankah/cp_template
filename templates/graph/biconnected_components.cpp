//finding bi connected componenets... 
const int maxN = 1e5 + 10;
vi adj[maxN];
si articulation_points;
int vis[maxN], in[maxN], low[maxN];
int timer; // initialized in solve
vector<vector<pair<int, int>>> bcc;
stack<pi> st;

void dfs(int node, int parent = -1)
{
    vis[node] = 1;
    in[node] = low[node] = ++timer;   
    int children = 0;
    for (int &child : adj[node])
    {
        if (child == parent)
            continue;
        if (vis[child])
        {
            // back edge to an ancestor: push when it's an ancestor (in[child] < in[node])
            if (in[child] < in[node]) {
                st.push({node, child});
            }
            low[node] = min(low[node], in[child]);
        }
        else
        {
            // forward (tree) edge
            st.push({node, child});
            dfs(child, node);
            if (low[child] >= in[node] || parent == -1)
            {
                vpi curr_bcc;
                while (!st.empty() && st.top() != make_pair(node, child) && st.top() != make_pair(child, node))
                {
                    curr_bcc.push_back(st.top());
                    st.pop();
                }
                if (!st.empty()) {
                    curr_bcc.push_back(st.top());
                    st.pop();
                }
                bcc.push_back(curr_bcc);
            }

            low[node] = min(low[node], low[child]);
            children++;
        }
    }
    if (parent == -1 && children > 1)
    {
        articulation_points.insert(node);
    }
}

//================ Code starts here ================
void solve()
{
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
        vis[i] = 0;
        in[i] = low[i] = 0;
    }
    while (!st.empty()) st.pop();
    bcc.clear();
    articulation_points.clear();
    timer = 0;

    while (m--)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            dfs(i);
            vpi curr_bcc;
            while (!st.empty())
            {
                curr_bcc.push_back(st.top());
                st.pop();
            }
            if (!curr_bcc.empty())
                bcc.push_back(curr_bcc);
        }
    }
    cout << "bcc are:" << '\n';
    for (auto &component : bcc)
    {
        for (auto &edge : component)
        {
            cout << edge.first << "-" << edge.second << ", ";
        }
        cout << '\n';
    }
}

//================ Code starts here ================
void solve()
{
    int n, m;
    cin >> n >> m;
    while (m--)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            dfs(i);
            vpi curr_bcc;
            while (!st.empty())
            {
                curr_bcc.pb(st.top());
                st.pop();
            }
            if (!curr_bcc.empty())
                bcc.pb(curr_bcc);
            
        }
    }
    cout << "bcc are:" << nl;
    for (auto &component : bcc)
    {
        for (auto &edge : component)
        {
            cout << edge.first << "-" << edge.second << ", ";
        }
        cout << nl;
    }
}
