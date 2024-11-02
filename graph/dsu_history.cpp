struct DSU {
    vector<int> par;
    vector<int> size;
    // when unite only size[largerGroup] and par[smallerGroup] change => we restore value at that index
    vector<pair<int,int>> sz_history; // pair: index to access - prev value 
    vector<pair<int,int>> par_history;
    DSU(int n) {
        par.resize(n + 1);
        fill(all(par), -1);
        size.resize(n + 1);
    }
    void make_set(int x) {
        if (par[x] == -1) {
            par[x] = x;
            size[x] = 1;
        }
    }
    int find(int x) {
        return par[x] == x ? x : find(par[x]); // history can not restore path compression, DO NOT PATH COMPRESSION => logn average find(a)
    }
    void unite(int a, int b) {
        int ra = find(a);
        int rb = find(b);

        if (size[ra] < size[rb]) swap(ra, rb);

        // save history before modifying current value
        sz_history.push_back({ra, size[ra]}); // index - value
        par_history.push_back({rb, par[rb]});
        
        if (ra != rb) {
            size[ra] += size[rb];
            par[rb] = ra;
        }
    }
    void rollback(int step) {
        while (step-- && sz_history.size()) {
            auto sz_p = sz_history.back();
            auto par_p = par_history.back();
            size[sz_p.first] = sz_p.second;
            par[par_p.first] = par_p.second;

            sz_history.pop_back();
            par_history.pop_back();
        }
    }
    bool same_set(int a, int b) {
        return find(a) == find(b);
    }
};


int main() {
    DSU dsu(1000);
    dsu.make_set(1);
    dsu.make_set(2);
    dsu.unite(1, 2); // add edge
    dsu.rollback(1); // remove previous added edge
}
