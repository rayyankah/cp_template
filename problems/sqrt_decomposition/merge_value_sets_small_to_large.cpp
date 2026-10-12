//update x with y, move smaller to bigger set..#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);   // Disable synchronization for faster input/output
    cin.tie(nullptr);              // Untie cin from cout to avoid unnecessary flushes

    int N, Q;
    cin >> N >> Q;                // Read the size of the array and number of queries

    vector<long long> a(N + 1);    // Array to store the values, 1-indexed
    unordered_map<long long, unordered_set<int>> pos;  // Map to store sets of indices for each value
    pos.reserve(N * 2);           // Reserve space for the map to avoid rehashing

    // Fill the array and the map
    for (int i = 1; i <= N; i++) {
        cin >> a[i];              // Read the value at each index
        pos[a[i]].insert(i);      // Insert the index into the set of the value
    }

    // Process each query
    while (Q--) {
        int type;
        cin >> type;             // Read the type of query (1 or 2)

        if (type == 1) {
            long long X, Y;
            cin >> X >> Y;       // Read the values for the type 1 query

            if (X == Y) continue; // If X == Y, no change is needed

            auto &sx = pos[X];    // Set of indices for value X
            auto &sy = pos[Y];    // Set of indices for value Y

            if (sx.empty()) continue;  // If no indices hold value X, continue

            // Always merge the smaller set into the larger one
            if (sx.size() > sy.size()) {
                swap(sx, sy);         // Swap the sets if X's set is larger
                swap(X, Y);           // Swap the values too to maintain consistency
            }

            // Move each index from X's set into Y's set and update a[idx] = Y
            for (int idx : sx) {
                a[idx] = Y;           // Update the value at the index
                sy.insert(idx);       // Insert the index into the Y's set
            }
            sx.clear();               // X no longer holds any indices

        } else if (type == 2) {
            int idx;
            cin >> idx;              // Read the index for type 2 query
            cout << a[idx] << '\n';   // Output the value at the given index
        }
    }

    return 0;
}
