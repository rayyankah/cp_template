//finding bridge:const int maxN = 1e5 + 10;
vi adj[maxN];
int vis[maxN], in[maxN], low[maxN];
int timer;//initialized to 0
void dfs(int node, int parent){
    vis[node]=1;
    in[node]=low[node]=timer++;//initialize in and low time to itself first
    for(int child: adj[node]){
        if(child==parent)continue;
        if(vis[child]==1){
            //back edge
            low[node]=min(low[node],in[child]);
        }
        else{
            //forward edge
            dfs(child,node);
            if(low[child]>in[node]){
                //there is no other path to reach child or its descendants
                cout<<"ahare ! "<<node<<" - "<<child<<" is a bridge"<<nl;
            }
            //try to minimize low time of parent using child low time
            low[node]=min(low[node],low[child]);
            
        }
    }
}
