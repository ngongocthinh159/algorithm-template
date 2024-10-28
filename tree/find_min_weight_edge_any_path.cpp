#define LOG 20
int n, m, q;
vector<ll> path_sum;
vector<vector<pair<int,int>>> g;
vector<vector<int>> par;
vector<int> depth;
vector<vector<int>> mn;
void dfs(int u, int dir_par, ll sum, int level) {
    depth[u] = level;
    path_sum[u] = sum;
    for (auto p : g[u]) {
        if (p.first != dir_par) {
            mn[p.first][0] = p.second; // populate mn[i][2^0]: for each node compare it with its parent
            par[p.first][0] = u;
            dfs(p.first, u, sum + p.second, level + 1);
        }
    }
}
int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int k = depth[u] - depth[v];
    for (int j = LOG; j >= 0; j--) {
        if ((k >> j) & 1) u = par[u][j];
    }
    if (u == v)  return u;
    for (int j = LOG; j >= 0; j--) {
        if (par[u][j] != par[v][j]) {
            u = par[u][j];
            v=par[v][j];
        }
    }
    return par[u][0];
}
int minWeightToLCA(int u, int lca_u) {
    int k = depth[u] - depth[lca_u];
    int ans = 1e9;
    for (int j = LOG; j >= 0; j--) {
        if ((k >> j) & 1) {
            ans = min(ans, mn[u][j]);
            u = par[u][j];
        }
    }
    return ans;
}
int minWeigthInPath(int u, int v) {
    int lcauv = lca(u, v);
    if (lcauv == u) {
        return minWeightToLCA(v, u);
    } else if (lcauv == v) {
        return minWeightToLCA(u, v);
    }
    return min(minWeightToLCA(u, lcauv), minWeightToLCA(v, lcauv));
}
void pre_compute() {

}
void solve() {
    cin >> n >> m;
    g.resize(n + 1);
    path_sum.resize(n + 1);
    par = vector<vector<int>>(n + 1, vector<int>(LOG + 1));
    depth.resize(n + 1);
    mn = vector<vector<int>>(n + 1, vector<int>(LOG + 1));
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    
    par[1][0] = 0;
    dfs(1, -1, 0, 0);
    for (int j = 1; j <= LOG; j++) {
        for (int i = 1; i <= n; i++) {
            par[i][j] = par[par[i][j - 1]][j - 1];
            if (par[i][j] != 0) mn[i][j] = min(mn[i][j - 1], mn[par[i][j - 1]][j - 1]);
        }
    }
    cin >> q;
    for (int i = 0; i< q; i++) {
        int u, v; cin >> u >> v;
        cout << minWeigthInPath(u, v) << nline;
    }
}