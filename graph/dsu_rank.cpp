struct DSU {
    vector<int> parent;
    vector<int> rank;
    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1);
    }
    void make_set(int x) {
        parent[x] = x;
        rank[x] = 0;
    }
    int find(int x) {
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    }
    bool same_set(int a, int b) {
        return find(a) == find(b);
    }
    void unite(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra != rb) {
            if (rank[ra] < rank[rb]) swap(ra,rb);
            if (rank[ra] == rank[rb]) rank[ra]++;
            parent[rb] = ra;
        }
    }
};
