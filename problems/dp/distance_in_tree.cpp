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
