int n;
vector<vector<int>> g(2e5 + 5);
void pre_compute() {
 
}
// return {depth, node}
pair<int,int> dfs(int u, int par, int depth) {
    if (g[u].size() == 1 && g[u][0] == par) return {depth, u};
    pair<int,int> res = {-1, -1};
    for (auto v : g[u]) {
        if (v != par) {
            auto p = dfs(v, u, depth + 1);
            if (res.first < p.first) {
                res = p;
            }
        }
    }
    return res;
}
void solve() {
    cin >> n;
    if (n == 1) {
        cout << 0 << nline;
        return;
    }
    int u,v ; 
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto pa = dfs(1, -1, 0);
    auto pb = dfs(pa.second, -1, 0);
    cout << pb.first << nline; // tree diameter is depth of second dfs
}