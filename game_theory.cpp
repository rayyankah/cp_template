//hackerearth-->power beaker
void solve()
{
  int n,m;
  cin >>n>>m;
  m-=1;
  if(m==0){
    cout<<2<<nl;
    return;
  }
  if(n&1){
    cout<<1<<nl;
    return;
  }
  cout<<2<<nl;
}



//chess
int dp[16][16];
int func(int x, int y){
    
    if(x<1 || y<1 || x>15|| y>15){
        return 1;//amr jonno winning cz je dise she invalid move dise
    }
    if(dp[x][y]!=-1){
        return dp[x][y];
    }
    int ans = func(x-1,y-2)+func(x-2,y-1)+func(x-2, y+1)+func(x+1, y-2);
    if(ans<=3){
        return dp[x][y]=1;
    }
    return dp[x][y]=0;
}
//================ Code starts here ================
void solve()
{
  int x,y;

    cin >>x>>y;
    if(func(x,y)){
        cout<<"First"<<nl;
    }
    else{
        cout<<"Second"<<nl;
    }


}




//nim's game
void solve()
{
  int n;
  cin >>n;
  int ans =0;
  while(n--){
    int x;
    cin >>x;
    ans^=x;
  }
  if(ans==0){
    cout<<"Second"<<nl;
  }
  else{
    cout<<"First"<<nl;
  }
}

//misere nim
void solve()
{
    int n;
    cin >> n;
    int ans = 0;
    int numone = 0;
    int tempn = n;
    while (n--)
    {
        int x;
        cin >> x;
        if (x == 1)
            numone++;
        ans ^= x;
    }
    if (numone == tempn)
    {
        if (tempn & 1)
        {
            cout << "Second" << nl;
        }
        else
        {
            cout << "First" << nl;
        }
        return;
    }
    if (ans == 0)
    {
        cout << "Second" << nl;
    }
    else
    {
      
            cout << "First" << nl;
        
    }
}




//Nimble NIM
void solve()
{
  int n;
  cin>>n;
  int ans =0;
  for(int i=0;i<n; i++){
    int x;
    cin >>x;
    if(x&1){
        ans^=i;
    }
    
  }
  if(ans){
    cout<<"First"<<nl;
  }
  else{
    cout<<"Second"<<nl;
  }
}




//string grundy
#include <bits/stdc++.h>
using namespace std;

// ----------------- simple globals (user style) -----------------
string S;
int n;
vector<vector<int>> occ; // occ[i] = list of end indices (inclusive) of dictionary words that start at i

// Grundy table: g[l][r] for substring S[l..r)  (0 <= l < r <= n)
vector<vector<int>> g;

// helper to compute mex of small set
int mex_of(const vector<char> &seen) {
    int k = (int)seen.size();
    for (int i = 0; i < k; ++i) if (!seen[i]) return i;
    return k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // --- read input (adjust if needed) ---
    if (!(cin >> S)) return 0;
    int m;
    cin >> m;
    vector<string> dict(m);
    for (int i = 0; i < m; ++i) cin >> dict[i];

    n = (int)S.size();
    occ.assign(n, vector<int>());

    // --- find all occurrences of each dictionary word in S ---
    // naive scanning; if you want faster, build Aho-Corasick
    for (int i = 0; i < n; ++i) {
        for (int w = 0; w < m; ++w) {
            const string &pat = dict[w];
            int L = (int)pat.size();
            if (i + L <= n && S.compare(i, L, pat) == 0) {
                occ[i].push_back(i + L - 1); // store inclusive end index
            }
        }
    }

    // --- DP initialization ---
    g.assign(n + 1, vector<int>(n + 1, 0));
    // we will compute g[l][r] for lengths from 1..n (r = l+len)

    // define an upper bound on possible Grundy values to size the 'seen' array.
    // In practice Grundy values are small, but we pick something like 512.
    const int MAXG = 512;

    for (int len = 1; len <= n; ++len) {
        for (int l = 0; l + len <= n; ++l) {
            int r = l + len;
            // collect reachable Grundy values
            // we use a boolean array to mark seen XOR values
            vector<char> seen(MAXG, 0);

            // iterate over all possible starts p inside [l, r-1]
            // and for each occurrence end e in occ[p] with e < r, add g[l][p] ^ g[e+1][r]
            for (int p = l; p < r; ++p) {
                if (occ[p].empty()) continue;
                int leftG = g[l][p];
                for (int e : occ[p]) {
                    if (e < r) {
                        int rightG = g[e + 1][r];
                        int val = leftG ^ rightG;
                        if (val < MAXG) seen[val] = 1;
                    }
                }
            }
            g[l][r] = mex_of(seen);
        }
    }

    int Gwhole = g[0][n];
    if (Gwhole == 0) {
        cout << "SECOND\n"; // second player wins
        return 0;
    } else {
        cout << "FIRST\n"; // first player wins
    }

    // If you also want to print a winning move (one possible deletion that makes XOR 0):
    // find any deletion S[i..j] that is a dictionary word and for which g[0][i] ^ g[j+1][n] == 0
    bool found = false;
    for (int i = 0; i < n && !found; ++i) {
        for (int e : occ[i]) {
            int newGr = g[0][i] ^ g[e + 1][n];
            if (newGr == 0) {
                cout << "Winning move: delete substring [" << i << "," << e << "] : '"
                     << S.substr(i, e - i + 1) << "'\n";
                found = true;
                break;
            }
        }
    }
    if (!found) {
        // theoretically shouldn't happen if Gwhole != 0
    }
    return 0;
}




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


//stoned game:
void solve() {
    int n;
    cin >> n;
    vi a(n);
    int sum = 0, mx = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
        mx = max(mx, a[i]);
    }
    if (mx > sum - mx) {
        cout << "T" << nl;
    } else {
        cout << ((sum & 1) ? "T" : "HL") << nl;
    }
}



//https://codeforces.com/gym/101908/problem/B
//grundy
const int INF = 1 << 30;
int dp[101][101];

int get_grundy(int l, int c) {
    if (l == 0 || c == 0 || l == c) return INF;
    if (dp[l][c] != -1) return dp[l][c];
    set<int> s;
    for (int u = 1; u <= l; u++) s.insert(get_grundy(l - u, c));
    for (int u = 1; u <= c; u++) s.insert(get_grundy(l, c - u));
    for (int u = 1; u <= min(l, c); u++) s.insert(get_grundy(l - u, c - u));
    int mex = 0;
    while (s.count(mex)) mex++;
    return dp[l][c] = mex;
}

//================ Code starts here ================
void solve()
{
    int n;
    cin >>n;
    int grid[n][n];
    memset(dp, -1, sizeof(dp));
        int maxL = -1;
    int maxR = -1;
    vpi in;
    vi first(105,0);
    rep(i,0,n){
        int l,r;
        cin >>l>>r;
        maxL  =max(maxL , l);
        maxR = max(maxR, r);
        in.pb({l,r});
    }
    int xxor =0;
    rep(i,0,n){
        int l = in[i].first;
        int r = in[i].second;
        xxor^= get_grundy(l,r);
        
    }
    if(xxor){
        cout<<'Y'<<nl;
    }
    else{
        cout<<'N'<<nl;
    }
}

