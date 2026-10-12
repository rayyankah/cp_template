//tree hash
void solve()
{
   //seeing if two trees identical using hashing
   int n,m;
   cin >>n>>m;
   vvi adj1(n+1);
   vvi adj2(n+1);

   rep(i,0,n-1){
    int u,v;
    cin >>u>>v;
    adj1[u].pb(v);
    adj1[v].pb(u);

   }
    rep(i,0,m-1){
     int u,v;
     cin >>u>>v;
     adj2[u].pb(v);
     adj2[v].pb(u);
    }
    vi hash1(n+1,0);
    vi hash2(m+1,0);
    vi subtree_size1(n+1,0);
    vi level1(n+1,0);
    vi subtree_size2(n+1,0);
    vi level2(n+1,0);
    function<void(int,int, vi&, vi&, vvi&, vi&)>dfs1  = [&](int node, int par, vi &level, vi& subtree_size, vvi &adj, vi &hash){
        subtree_size[node]=1;
        if(par!=-1) level[node]=level[par]+1;

        for(auto &child: adj[node]){
            if(child==par)continue;
            dfs1(child,node,level,subtree_size,adj,hash);
            subtree_size[node]+=subtree_size[child];
            //hash[node] = (hash[all_children] + d* b^p// d->subtree size, b->prime, p->level)
            hash[node]+=hash[child];
        }
        hash[node]+=(subtree_size[node]*binExp(31,level[node]))%MOD;
        hash[node]%=MOD;

    };
    level1[1]=0;
    level2[1]=0;
    dfs1(1,-1,level1,subtree_size1,adj1,hash1);
    dfs1(1,-1,level2,subtree_size2,adj2,hash2);
    if(hash1[1]==hash2[1])cout<<"YES"<<nl;
    else cout<<"NO"<<nl;
}
