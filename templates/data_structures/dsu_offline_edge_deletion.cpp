//offline dsu solution:  cin >> n >> m >> q;
    vector<pair<int,int>> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second; // 1-indexed nodes assumed
    }

    vector<int> queries(q);
    vector<bool> removed(m, false);

    // queries[i] holds the index (0-based) of the edge to delete at step i
    for (int i = 0; i < q; i++) {
        cin >> queries[i];
        queries[i]--;                 // convert to 0-index
        removed[queries[i]] = true;   // mark as "will be deleted" -> so initially absent
    }

    // Initialize DSU for all nodes
    for (int i = 1; i <= n; i++) make(i);

    int components = n;  // initially each node is its own component

    // Build the initial graph = all edges except those marked "removed"
    // (because we are preparing the state *after all deletions*)
    for (int i = 0; i < m; i++) {
        if (!removed[i]) {
            int u = edges[i].first, v = edges[i].second;
            if (find(u) != find(v)) {
                Union(u, v);
                components--;         // two components merged into one
            }
        }
    }

    vector<int> ans(q);
    // Process queries in reverse:
    // at step i (going backwards), before adding back the edge, the number of
    // components is exactly the answer for the forward deletion at i.
    for (int i = q - 1; i >= 0; i--) {
        ans[i] = components;  // store current component count as the answer
        int u = edges[queries[i]].first, v = edges[queries[i]].second;

        // Now "undo" the deletion by adding the edge back.
        // If the endpoints are in different components, they will merge.
        if (find(u) != find(v)) {
            Union(u, v);
            components--;     // merged -> one fewer component
        }
    }

    // Print answers in forward order
    for (int x : ans) cout << x << "\n";
