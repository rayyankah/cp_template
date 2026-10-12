//berland
void dfs(vector<vpii> &graph,vvi &dp,vector<vvi> &ans,int u,int p) {
    int k=dp[0].size();
    dp[u][1]=0;
    for (auto e : graph[u]) {
        int v=e.first;
        int ind=e.second;
        if (v!=p) {
            dfs(graph,dp,ans,v,u);
            for (int i=1; i<k; ++i) {
                dp[v][i]++;
                ans[v][i].push_back(ind);
            }
            for (int i=k-1; i>=1; --i) {
                dp[u][i]++;
                ans[u][i].push_back(ind);
                for (int j=1; j<=i; ++j) {
                    if (dp[u][i-j]+dp[v][j]-1<dp[u][i]) {
                        dp[u][i]=dp[u][i-j]+dp[v][j]-1;
                        ans[u][i].clear();
                        for (auto x : ans[u][i-j]) {
                            ans[u][i].push_back(x);
                        }
                        for (int l=0; l<ans[v][j].size()-1; ++l) {
                            ans[u][i].push_back(ans[v][j][l]);
                        }
                    }
                }
            }
        }
    }
}
 
int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    int n,k;
    cin >> n >> k;
    vector<vpii> graph(n);
    for (int i=1; i<n; ++i) {
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back({b,i});
        graph[b].push_back({a,i});
    }
    vvi dp(n,vi(k+1,1e9));
    vector<vvi> ans(n,vvi(k+1));
    dfs(graph,dp,ans,0,-1);
    vi v;
    int s=1e9;
    for (int i=0; i<n; ++i) {
        if (dp[i][k]<s) {
            s=dp[i][k];
            v=ans[i][k];
        }
    }
    cout << s << endl;
    for (auto item : v) cout << item << ' ';
    cout << endl;
}
