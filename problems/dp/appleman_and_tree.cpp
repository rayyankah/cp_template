//appleman
int ex(int a,int n){ int res = 1;while(n){if(n&1){res = (res*a)%MOD;}a = (a*a)%MOD;n >>= 1LL;}return res;}
vector<int>edge[N];
int f[N][2],ok[N],col[N];
void dfs(int v,int p){
    ok[v] = col[v];
    vector<pii>f0;
    int c0 = 1,c00 = 1,c1 = 1,s1 = 0;
    for(auto u : edge[v]){
        if(u == p) continue;
        dfs(u,v);
        ok[v] |= ok[u];
        if(ok[u]&&col[u] == 0){
            c0 = (c0*((f[u][0]+f[u][1])%MOD))%MOD;
            f0.push_back({f[u][1],(f[u][0]+f[u][1])%MOD});
        } if(col[u] == 1){
            c1 = (c1*f[u][1])%MOD;
            ++s1;
        }
    }
    if(col[v] == 0){
        f[v][0] = (c0*c1)%MOD;
        f[v][1] = (((c0*c1)%MOD)*s1)%MOD;
        for(auto i : f0){
            int cur = (((((c1*c0)%MOD)*i.fi)%MOD)*imod(i.se))%MOD;
            f[v][1] = (f[v][1]+cur)%MOD;
        }
    } else{
        f[v][1] = ((c0*c1)%MOD)%MOD;
    }
}
void solve(){
    int n;
    cin >> n;
    for(int i = 2;i <= n;++i){
        int u;
        cin >> u;
        edge[++u].push_back(i);
        edge[i].push_back(u);
    }
    for(int i = 1;i <= n;++i){
        cin >> col[i];
    }
    dfs(1,1);
    cout << f[1][1];
}
