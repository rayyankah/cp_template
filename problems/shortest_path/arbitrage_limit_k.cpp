#include <bits/stdc++.h>
using namespace std;

#define vll vector<long long>
#define ll long long

void solve_arbitrage_limit_k() {
    int n;
    cin >> n;

    // Map to assign indices to currency names
    map<string, int> mp;
    for (int i = 1; i <= n; i++) {
        string s; 
        cin >> s;
        mp[s] = i;
    }

    int m; // number of exchange rates
    cin >> m;

    // Initialize exchange rates matrix for maximum product
    vector<vector<long double>> dist(n + 1, vector<long double>(n + 1, -1.0));
    for (int i = 1; i <= n; i++) {
        dist[i][i] = 1.0;  // distance to itself is always 1
    }

    // Read the exchange rates
    for (int i = 0; i < m; i++) {
        string a, b;
        long double r;
        cin >> a >> r >> b;

        int u = mp[a], v = mp[b];
        dist[u][v] = max(dist[u][v], r);  // Set the maximum exchange rate
    }

    int K; // maximum number of exchanges
    cin >> K;

    // Perform the modified Floyd-Warshall with the step limit (max K exchanges)
    vector<vector<vector<long double>>> dp(K + 1, vector<vector<long double>>(n + 1, vector<long double>(n + 1, -1.0)));

    // Base case: with 0 exchanges, the only path is direct exchange (dist[i][j])
    for (int i = 1; i <= n; i++) {
        dp[0][i][i] = 1.0;
    }

    // Initialize the first level of exchanges (single exchange)
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[1][i][j] = dist[i][j];  // Direct exchange rates
        }
    }

    // Apply Floyd-Warshall with up to K exchanges
    for (int k = 2; k <= K; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                for (int intermediate = 1; intermediate <= n; intermediate++) {
                    if (dp[k - 1][i][intermediate] >= 0 && dp[1][intermediate][j] >= 0) {
                        dp[k][i][j] = max(dp[k][i][j], dp[k - 1][i][intermediate] * dp[1][intermediate][j]);
                    }
                }
            }
        }
    }

    // Check for arbitrage: if any diagonal value is > 1.0, arbitrage is possible
    for (int k = 1; k <= K; k++) {
        for (int i = 1; i <= n; i++) {
            if (dp[k][i][i] > 1.0) {
                cout << "Yes\n";
                return;
            }
        }
    }

    cout << "No\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve_arbitrage_limit_k();
    return 0;
}
