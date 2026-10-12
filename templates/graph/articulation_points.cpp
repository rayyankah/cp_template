//articulation points
const int maxN = 1e5 + 10;
vi adj[maxN];
si articulation_points;
int vis[maxN], in[maxN], low[maxN];
int timer;//initialized to 0
void dfs(int node, int parent=-1){
    vis[node]=1;
    in[node]=low[node]=timer++;
    int children =0;
    for(int &child: adj[node]){
        if(child==parent)continue;
        if(vis[child]){
            //back edge
            low[node]=min(low[node],in[child]);
        }
        else{
            //forward edge
            dfs(child,node);
            if(low[child]>=in[node] && parent!=-1){
                //articulation point
                //root node is handled separately
                articulation_points.insert(node);
            }
            low[node]=min(low[node],low[child]);
            children++;
        }
    }
    if(parent==-1 && children>1){
        articulation_points.insert(node);
        //root node is an articulation point if it has more than 1 child
        //set is used to avoid duplicates
    }

}
