class TreeAncestor {
    vector<vector<int>>up;
    vector<int>depth;
    int LOG = 20;
    //20 is enough for 1e5 nodes
public:
    TreeAncestor(int n, vector<int>& parent) {
        up = vector<vector<int>>(n,vector<int>(LOG));
        parent[0]=0;
        depth = vector<int>(n,-1);
        for(int i=1; i<n; i++){
            depth[i]=dfs_find_depth(i, parent);
        }
        for(int i=0; i<n; i++){
            up[i][0]=parent[i];//2^0 th ancestor = parent;
        }
        for(int j=1; j<LOG;j++){
            for(int i=0; i<n; i++){
                up[i][j]= up[up[i][j-1]][j-1];
            }
        }

    }
    int dfs_find_depth(int n, vector<int>&parent){
        if(n==0){
            depth[0]=0;
            return depth[0];
        }
        if(depth[n]!=-1){
            return depth[n];
        }
        return depth[n]=dfs_find_depth(parent[n], parent)+1;

    }
    int getKthAncestor(int node, int k) {
        if(k>depth[node])return -1;
        for(int j=LOG-1; j>=0; j--){
            if((1<<j)&k){
                node=  up[node][j];//19 = 16+2+1;
            }
        }
        return node;
    }
};


// getting lca code
const int maxN = 2e5+10;
vi depth(maxN);
vvi children(maxN);
const int LOG = 20;
vvi up(maxN, vi(LOG));

void dfs_find_up(int n){
    for(int v: children[n]){
        up[v][0]=n;//n is parent of v
        depth[v]=depth[n]+1;
        for(int j=1;j<LOG; j++){
            up[v][j]=up[up[v][j-1]][j-1];
        }
        dfs_find_up(v);
    }
}
int get_lca(int u, int v){
    if(depth[u]<depth[v]){
        swap(u,v);
    }
    int k = depth[u]-depth[v];
    for(int j=LOG-1; j>=0; j--){
        if(k&(1<<j)){
            u=up[u][j];//going to kth ancestor
        }
    }
    if(u==v)return v;//v is the parent of u, so lca(u,v)=v
    //now they are on the same level.. we will take them to just below the lca
    for(int j=LOG-1; j>=0; j--){
        if(up[u][j]!=up[v][j]){
            //those ancestors are not the same, so below the lca
            u= up[u][j];
            v = up[v][j];
        }
    }
    //now they are just below lca
    return up[u][0];//or up[v][0];
}


//================ Code starts here ================
void solve()
{
  int n;
  cin >>n;
  rep(i,0,n){
    int m;
    cin >>m;
    dfs_find_up(0);//don't forget..
    while(m--){
        int child;
        cin >>child;
        children[i].pb(child);
    }
  }

  int q;
  cin>>q;
  while(q--){
    int u,v;
    cin >>u>>v;
    cout<<get_lca(u,v)<<nl;
  }
}
