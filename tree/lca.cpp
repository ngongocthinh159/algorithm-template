#define LOG 19 // can be 17, 18, 19, 20 as long as more than the number of tree nodes
const int mxN = 1e5 + 5;
int par[mxN][LOG + 1];
int height[mxN], direct_par[mxN];
// sta and fin TAG in dfs travel order: imagine each root node manage a range of nodes which are all childs in the subtree
// u is ancestor of v <=>    sta[u] <= sta[v] <= fin[u]
int sta[mxN], fin[mxN]; 

void dfs(int u) {
    node_cnt[u] = 1;
    sta[u] = cnt++;
    for (auto v : g[u]) {
        if (v != direct_par[u]) {
            direct_par[v] = u;
            height[v] = height[u] + 1;

            par[v][0] = u;
            for (int i = 1; i <= LOG; i++) {
                par[v][i] = par[par[v][i - 1]][i - 1];
            }

            dfs(v);
            node_cnt[u] += node_cnt[v];
        }
    }
    fin[u] = sta[u] + node_cnt[u] - 1;
}

int lca(int u, int v) {
    if (height[u] < height[v]) swap(u, v);

    // equalize height
    // after jump the u height stil >= v height => jump
    for (int i = LOG; i >= 0; i--) {
        if (height[par[u][i]] >= height[v]) u = par[u][i];
    }
    if (u == v) return u;

    // jump to furthest node that is not the same (the node just below LCA)
    for (int i = LOG; i >= 0; i--) {
        if (par[u][i] != par[v][i]) {
            u = par[u][i];
            v = par[v][i];
        }
    }
    
    return par[u][0];
}

// jump 2^j edges from u
int jump(int u, int j) {
    for (int i = LOG; i >= 0; i--) {
        if (j & (1 << i)) u = par[u][i];
    }
    return u;
}

// Usage
void pre_process() {
    build_graph();

    // make sure root jump to any level must point to dummy
    // make sure dummy jump to any level must point to itself
    // If needed:
    /**
     * for (int i = 0; i <= LOG; i++) {
     *  par[root][i] = dummy;
     *  par[dummy][i] = dummy;
     * }
    */
    dfs(root);
    height[dummy] = -1; // must set dummy height = -1 for: height[par[u][i]] >= height[v] in LCA always correct

    lca(u, v);
}