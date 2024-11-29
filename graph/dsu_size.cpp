struct DSU {
    vector<int> parent;
    vector<int> size;
    DSU(int n, bool auto_make_set = true) {
        parent.resize(n + 1);
        size.resize(n + 1);
        if (auto_make_set) {
            for (int i = 0; i <= n; i++) parent[i] = i, size[i] = 1;
        }
    }
    void make_set(int x) {
        parent[x] = x;
        size[x] = 1;
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
            if (size[ra] < size[rb]) swap(ra,rb);
            size[ra] += size[rb];
            parent[rb] = ra;
        }
    }
    int find_size(int x) {
        return size[find(x)];
    }
};
