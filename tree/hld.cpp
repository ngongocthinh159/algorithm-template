// SegmentTree must support lazy propagation (if HLD requires segment update on chains)
template <typename SegmentTree>
struct HLD {
    int n, T;
    vector<int> big, chain, par, depth, euler, pos;
    SegmentTree segtree;

    int dfs_sz(int u, int p, vector<vector<int>>& g) {
        big[u] = -1;
        int mxc = 0;
        int u_sz = 1;
        for (auto v : g[u]) if (v != p) {
            par[v] = u;
            depth[v] = depth[u] + 1;
            int v_sz = dfs_sz(v, u, g);
            u_sz += v_sz;
            if (mxc < v_sz)
                mxc = v_sz, big[u] = v;
        }
        return u_sz;
    }

    void dfs_chain(int u, int p, int top, vector<int>& val, vector<vector<int>> &g) {
        euler[++T] = val[u];
        pos[u] = T;
        chain[u] = top;
        if (big[u] != -1)
            dfs_chain(big[u], u, top, val, g);
        for (auto v : g[u]) if (v != p && v != big[u])
            dfs_chain(v, u, v, val, g);
    }

public:
    HLD(vector<vector<int>>& g, vector<int> &val, int root = 1) {
        n = g.size();
        T = -1;
        big.resize(n + 1);
        chain.resize(n + 1);
        par.resize(n + 1);
        depth.resize(n + 1);
        pos.resize(n + 1);
        euler.resize(n + 1);

        dfs_sz(root, -1, g);
        dfs_chain(root, -1, root, val, g);
        segtree = SegmentTree(euler);
    }

    int query_lca(int u, int v) {
        while (chain[u] != chain[v]) {
            if (depth[chain[u]] < depth[chain[v]]) swap(u, v);
            u = par[chain[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        return u;
    }

    int query(int u, int v) {
        int res = 0;
        while (chain[u] != chain[v]) {
            if (depth[chain[u]] < depth[chain[v]]) swap(u, v);
            res += segtree.query(pos[chain[u]], pos[u]).sum;
            u = par[chain[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        res += segtree.query(pos[u], pos[v]).sum;
        
        // u is LCA now

        return res;
    }

    void update(int u, int v, int val) {
        while (chain[u] != chain[v]) {
            if (depth[chain[u]] < depth[chain[v]]) swap(u, v);
            segtree.update(pos[chain[u]], pos[u], val, Node::PLUS);
            u = par[chain[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        segtree.update(pos[u], pos[v], val, Node::PLUS);

        // u is LCA now
    }
};
