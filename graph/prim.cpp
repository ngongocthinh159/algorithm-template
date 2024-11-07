// Find MST for dense graph O(E*logV)
void prim(vector<vector<pair<int,ll>>> &g) {
    set<pair<ll,int>> S; // min edge to node - node number
    vector<pair<ll,int>> min_e(n + 1, {LINF,-1}); // cur min edge to a node and parent of edge (u -> v then u is parent)
    vector<bool> visited(n + 1); // explored nodes
    ll minMST = 0; // min weight of MST
    vector<pair<int,int>> selectedEdges; // selected edges in MST

    S.insert({0,1}); // choose node 1 as the first node to explore, edge to 1 weight = 0 (dummy edge)
    min_e[1] = {0,-1}; // parent of edge to 1 = -1 (dummy edge)

    while (S.size()) {
        auto p = *S.begin();
        S.erase(S.begin());
        int u = p.second;
        int w_par_u = p.first;
        int par = min_e[u].second;
        
        minMST += w_par_u;
        visited[u] = true;
        if (par != -1) selectedEdges.push_back({par, u});

        for (auto _p : g[u]) {
            int v = _p.first;
            ll w_uv = _p.second;
            if (!visited[v] && min_e[v].first > w_uv) {
                S.erase({min_e[v].first, v});
                min_e[v] = {w_uv, u};
                S.insert({min_e[v].first, v});
            }
        }
    }
    if (sz(selectedEdges) < n - 1) {
        cout << "MST not existed" << nline;
    } else {
        cout << minMST << nline;
        for (auto e : selectedEdges) {
            cout << e.first << " " << e.second << nline;
        }
    }
}
