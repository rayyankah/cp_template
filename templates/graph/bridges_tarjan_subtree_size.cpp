// bridge -> any edge on who's removal the graph becomes disconnected and no of connected components +=1
//  time[] - > time of first visit of a node
//  low[] -> lowest time of visit of a node that can be reached from the subtree of that node (including itself)-> (not including parent)
//  case 1: u-v edge, time[u] < low[v] -> v cannot reach any ancestor of u, so u-v is a bridge
//  case 2: time[u] >= low[v] -> v can reach an ancestor of u, even if that edge is removed, so u-v is not a bridge
//  this algorithm is called tarjan's algo
// just find the bridges, the subtree sizes,
//  u->v  sub[v]* (n-sub[v]) hobe reduced pairs

void tarjan_dfs(vvi &adj, vi &subtree_size, vi &time, vi &low, int &timer, int u, int parent, vpi &bridges)
{
    time[u] = low[u] = timer;
    timer++;
    subtree_size[u] = 1;
    for (auto &child : adj[u])
    {
        if (child == parent)
            continue;
        if (time[child] == -1)
        {
            tarjan_dfs(adj, subtree_size, time, low, timer, child, u, bridges);
            subtree_size[u] += subtree_size[child];
        }
        low[u] = min(low[u], low[child]);
        if (time[u] < low[child])
        {
            bridges.pb({u, child});
        }
    }
}
