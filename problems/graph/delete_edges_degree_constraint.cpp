//deleting edge to satisafy D[u] for every u
void solve()
{
  int n,m;
  cin >>n>>m;
  vvi adj(n+1);
  vi deg(n+1, 0);
  vpi edges;
  rep(i,0,m){
    int u,v;
    cin >>u>>v;
    adj[u].pb(v);
    adj[v].pb(u);
    deg[u]++;
    deg[v]++;
    edges.emplace_back(u,v);
  }
  vi D(n+1);
  rep(i,1,n+1){
    cin >>D[i];
  }
  vi need(n+1);
  rep(i,1,n+1){
    need[i] = (deg[i]&1)^D[i];//if we need to change that degree
  }
  vi vis(n+1,0);
  vpi deletions;
  function<void(int,int)> dfs = [&](int u, int p){
    vis[u]=1;
    for(int child: adj[u]){
        if(child==p)continue;
        if(!vis[child]){
            //resolve child first
            dfs(child,u);
            if(need[child]==1){
                deletions.emplace_back(u,child);
                need[child]=0;
                if(need[u]==1){
                    need[u]=0;
                }
                else{
                    need[u]=1;
                }
            }
        }
    }
  };
  rep(i,1,n+1){
    if(!vis[i]){
        dfs(i,0);
        if(need[i]==1){
            cout<<-1<<nl;//impossible if neeed to toggle after resolving whole component
            return;
        }
    }
  }
  cout<<deletions.size()<<nl;
  for(auto &x: deletions){
    cout<<x.first<<" "<<x.second<<nl;
  }
}
