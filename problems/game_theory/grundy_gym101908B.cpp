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
