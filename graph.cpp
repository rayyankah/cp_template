//diameter of a tree
#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
vector<int> adj[N];
bool visited[N];
int n;

int farNode, maxDist;

void dfs(int u, int dist) {
    visited[u] = true;
    if (dist > maxDist) {
        maxDist = dist;
        farNode = u;
    }
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, dist + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // First DFS from node 1
    fill(visited, visited + n + 1, false);
    maxDist = -1;
    dfs(1, 0);

    // Second DFS from farNode
    fill(visited, visited + n + 1, false);
    maxDist = -1;
    dfs(farNode, 0);

    int diameter = maxDist;
    int ans = 2 * (n - 1) - diameter;
    cout << ans << "\n";

    return 0;
}






