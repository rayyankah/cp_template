///dice..
 const int N = 1e9+7;
    int numRollsToTarget(int n, int k, int target) {
        vector<vector<int>>dp(n+2,vector<int>(target+1,0));
        vector<vector<int>>csum(n+2,vector<int>(target+1,0));
        dp[n+1][0]=csum[n+1][0]=1;
        for(int i=0; i<=target; i++){
            csum[n+1][i]=1;
        }
        //csum[i][j]=sum of dp values in ith row(dices taken upto n) from 0 to j
        for(int dice=n; dice>=1; dice--){
            dp[dice][0]=csum[dice][0]=0;
            for(int val = 1; val<=target; val++){
                //face possible -->1 to k
                //face nibo 1 to k
                //val hbe val-1 to val-k -->csum[val-1]-csum[val-k-1]
                //but val jodi k theke choto hoy
                //face nibo 1 to val
                //val hbe val-1 to 0-->csum[val-1]
                if(val-k-1<00){
                    dp[dice][val]=((dp[dice][val]%N)+(csum[dice+1][val-1]%N))%N;
                    if(dp[dice][val]<0)dp[dice][val]+=N;
                }
                else{
                    dp[dice][val]+=(csum[dice+1][val-1]-csum[dice+1][val-k-1])%N;
                    if(dp[dice][val]<0)dp[dice][val]+=N;

                }
                csum[dice][val]=((csum[dice][val-1]%N)+(dp[dice][val]%N))%N;
                if(csum[dice][val]<0)csum[dice][val]+=N;
            }
        }
        return dp[1][target];

    }










//distance in tree -cf
const int maxN = 50005;
int k;//required len
vi adj[maxN];
vi dp[maxN];
int ans=0;
void dfs(int u, int p){
    dp[u].clear();
    dp[u].resize(k+1,0);
    dp[u][0]=1;
    debug(u,ans);
    // debug(u,p);
    for(int &child: adj[u]){
        if(child==p)continue;
        dfs(child,u);
        rep(i,0,k){
            ans+=dp[u][k-i-1]*dp[child][i];//avoiding dupicates, one path will count will only once
            //product hbe, not sum
        }
        rep(i,0,k){
            debug(u,child,dp[u],dp[child]);
            dp[u][i+1]+=dp[child][i];//cheler jonno jeta i len er path, bap er jonno sheta i+1 len er path
        }
    }
    debug(u,ans);


}

//================ Code starts here ================
void solve()
{
  int n;
  cin >>n>>k;
  int x;
//   ans=0;
//   rep(i,0,n+1){
//     adj[i].clear();
//     dp[i].clear();
//   }
  rep(i,0,n-1){
    int u,v;
    cin >>u>>v;
    x=u;
    adj[u].pb(v);
    adj[v].pb(u);
  }
//   debug(x);
  dfs(1,-1);
//     debug(k);
//   rep(i,0,n+1){
//     debug(dp[i]);
//   }
  cout<<ans<<nl;
  


}




//the queue
// const int N = 1005;
vvi adj(N);
vi dp(N);
vi subtree_size(N);
void dfs(int u, int p){
    int i =u;
    subtree_size[u] = 0;
    dp[u]=1;
    for(auto &v: adj[u]){
        if(v==p)continue;
        dfs(v,u);
        dp[i] = binMul(dp[i], dp[v], MOD);
        dp[i] = binMul(dp[i], inv[subtree_size[v]], MOD);
        dp[i]%=MOD;
        subtree_size[u]+=subtree_size[v];

    }
    dp[i]= binMul(dp[i], factorial[subtree_size[u]], MOD);
    subtree_size[u]++;
}

//================ Code starts here ================
void solve()
{
    int n;
    cin >> n;
    vi indeg(n + 1, 0);
    rep(i, 0, n - 1) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
        indeg[v]++;
    }
    // finding root (ceo of the company)
    int root = -1;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            root = i;
            break;
        }
    }
    dfs(root, -1);
    cout << dp[root] << nl;
}
signed main()
{
    fast;
    compute_factorials();
    int t = 1;
    cin >> t;
    int cas = 1;
    while (t--)
    {
        cout << "Case " << cas << ": ";
        // clear adj, dp, subtree_size for each test case
        for (int i = 1; i <= 1000; i++) {
            adj[i].clear();
            dp[i] = 0;
            subtree_size[i] = 0;
        }
        solve();
        cas++;
    }
}  








//just another robbery
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

//================ Code starts here ================
void solve(int t)
{
    double p;
    int n;
    cin >> p>>n;
    vi values(n);
    vector<double>prob(n);
    rep(i,0,n){
        cin >> values[i]>>prob[i];
    }
    double dp[n+1][10001];
    double ans =0;

    memset(dp,0,sizeof(dp));
    dp[n][0]=1.0;
    rep(i,1,10001)dp[n][i]=0.0;
    repb(i,n-1,0){
        rep(j,0,10001){
            dp[i][j]=dp[i+1][j];
            if(j-values[i]>=0){
                dp[i][j]=max(dp[i][j], dp[i+1][j-values[i]]*(1-prob[i]));//probablity of not getting caught
            }

        }

    }
    repb(i,10000,0){
        if((1-dp[0][i])<=p){
            ans =i;
            break;
        }
    }
    cout<<"Case "<<t<<": ";
    cout<<ans<<nl;
}

signed main()
{
    fast;

    int t = 1;
    cin >> t;
    for(int i=1; i<=t; i++){
        solve(i);
    }
}






