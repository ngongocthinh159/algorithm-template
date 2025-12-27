
// undirected graph
int color[N], low[N], num[N];
int timer = 0;
vector<int> g[N];
void dfs2(int u, int p) {
    color[u] = 1;
    low[u] = num[u] = timer++;
    int child = 0;
    for (auto v : g[u]) if (v != p) {
        if (color[v] == 0) { // span edge
            dfs2(v, u);
            low[u] = min(low[u], low[v]);
            if (num[u] < low[v])
                IS_BRIDGE(u, v)
            if (num[u] <= low[v] && p != -1)
                IS_ARTICULATION_POINT(u);
            child++;
        } else if (color[v] == 1) { // back edge
            low[u] = min(low[u], num[v]);
        }
    }
    if (p == -1 && child > 1)
        IS_ARTICULATION_PONT(u);
    color[u] = 2;
}
