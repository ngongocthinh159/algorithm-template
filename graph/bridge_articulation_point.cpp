
// undirected graph
// Tarjan
int color[N], low[N], num[N];
int timer = 0;
vector<int> g[N];
void dfs(int u, int p) {
    color[u] = 1;
    low[u] = num[u] = timer++;
    int child = 0;
    for (auto v : g[u]) if (v != p) {
        if (color[v] == 0) { // span edge
            dfs(v, u);
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
    if (p == -1 && child > 1) // special case root node
        IS_ARTICULATION_PONT(u);
    color[u] = 2;
}



// undirected graph
// Back edge cross over method
// https://codeforces.com/blog/entry/68138
// dp[u]: number of back edge "cross over" the span edge connect u and parent of u
// if dp[u] == 0 => no back edge cross over => span edge connect u and parent of u is a bridge
int color[N], up[N], down[N];
void dfs(int u, int p) {
    color[u] = 1;
    int sumc = 0, child = 0;
    for (auto v : g[u]) if (v != p) {
        if (color[v] == 0) {
            dfs(v, u);
            child++;
            sumc += dp[v];
            if (dp[v] == 0) 
                IS_BRIDGE(u -> v);
        } else if (color[v] == 1) {
            down[v]++;
            up[v]++;
        }
    }
    dp[u] = up[u] - down[u] + sumc;
    if ((p == -1 && child > 1) || (p != -1 && sumc - down[u] == 0))
        IS_ARTICULATION_POINT(u);
    color[u] = 2;
}
