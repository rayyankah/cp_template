//cactus
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+5,mod=1e9+7;
vector<int> adj[N];
int low[N],num[N],id[N],dp[N],val[N],dep[N];
int timer=1,cnt=1,sz=0;
bool check[N],vis[N];
int st[N][35];
set<pair<int,int>> cau;
set<int> comp[N];
map<pair<int,int>,bool> mp,bri;
void dfs(int u,int p)
{
    check[u]=1;
    low[u]=num[u]=timer++;
    for(int v:adj[u]){
        if(v==p) continue;
        if(check[v]) low[u]=min(low[u],num[v]);
        else{
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]==num[v]) cau.insert({min(u,v),max(u,v)});
        }
    }
}
void dfs1(int u)
{
    sz++;
    id[u]=cnt;
    check[u]=1;
    for(int v:adj[u]){
        pair<int,int> e={min(u,v),max(u,v)};
        if(cau.find(e)!=cau.end()) continue;
        if(check[v]) continue;
        dfs1(v);
    }
}
void dfs2(int u,int p)
{
    st[u][0]=p;
    for(int j=1;j<=30;j++){
        st[u][j]=st[st[u][j-1]][j-1];
    }
    for(int v:comp[u]){
        if(v==p) continue;
        dp[v]+=dp[u];
        dep[v]=dep[u]+1;
        dfs2(v,u);
    }
}
int lca(int u,int v)
{
    if(dep[u]<dep[v]) swap(u,v);
    int kc=dep[u]-dep[v];
    for(int j=0;j<=30;j++){
        if((1<<j)&kc) u=st[u][j];
    }
    if(u==v) return u;
    for(int j=30;j>=0;j--){
        if(st[u][j]!=st[v][j]){
            u=st[u][j];
            v=st[v][j];
        }
    }
    return st[u][0];
}
int pw(int a,int b)
{
    if(b==0) return 1;
    int res=1;
    while(b>0){
        if(b&1) res=1ll*res*a%mod;
        a=1ll*a*a%mod;
        b/=2;
    }
    return res;
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int a=0;a<m;a++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1,0);
    for(int a=0;a<=n;a++){
        check[a]=0;
    }
    for(int a=1;a<=n;a++){
        if(!check[a]){
            sz=0;
            dfs1(a);
            cnt++;
            if(sz>1) val[id[a]]=1;
        }
    }
    for(int a=1;a<=n;a++){
        for(int b:adj[a]){
            if(id[a]==id[b]) continue;
            comp[id[a]].insert(id[b]);
            comp[id[b]].insert(id[a]);
        }
    }
    cnt--;
    for(int a=1;a<=cnt;a++){
        dp[a]=val[a];
    }
    dfs2(1,0);
    int q;
    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;
        int x=id[l],y=id[r];
        int s=lca(x,y);
        int ans=dp[x]+dp[y]-2*dp[s]+val[s];
        cout<<pw(2,ans)<<"\n";
    }
}
