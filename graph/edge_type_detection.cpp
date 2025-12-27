


// undirected graph
// span edge: edge of DFS spanning tree
// back edge: edge connect a descendant with a visited ancestor
int color[N];
void dfs(int u, int p) {
    color[u] = 1;
    for (auto v : g[u]) if (v != p) {
        if (color[v] == 0) {
            dfs(v, u);
            IS_SPAN_EDGE(u -> v);
        } else if (color[v] == 1) {
            IS_BACK_EDGE(u -> v);
        }
    }
    color[u] = 2;
}


// directed graph
// span edge: edge of DFS spanning tree
// back edge: edge connect a descendant with a visited ancestor
// forward edge: edge connect an ancestor with a visited descendant
// cross edge: edge connect two nodes in two different sub tree of the DFS spanning tree
int color[N], tin[N];
void dfs(int u, int p) {
    color[u] = 1;
    tin[u] = timer++;
    for (auto v : g[u]) if (v != p) {
        if (color[v] == 0) {
            dfs(v, u);
            IS_SPAN_EDGE(u -> v);
        } else if (color[v] == 1) {
            IS_BACK_EDGE(u -> v);
        } else if (color[v] == 2) {
            if (tin[u] < tin[v])    // check v is descendant of u
                IS_FORWARD_EDGE(u -> v)
            else                    // or v is in different sub tree of u
                IS_CROSS_EDGE(u -> v)
        }
    }
    color[u] = 2;
}

