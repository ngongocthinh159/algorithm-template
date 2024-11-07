// O(E + V)
// pass in: graph and reverted direction graph
vector<vector<int>> compos;
vector<pair<int,int>> bridges;
vector<int> compo_id;
vector<vector<int>> cg; // condensed graph
void dfs(int u, vector<bool> &vis, vector<int> &topo, vector<vector<int>> &g) {
    vis[u] = true;
    for (auto v : g[u]) {
        if (!vis[v]) dfs(v);
    }
    topo.push_back(u);
}
void dfs2(int u, vector<bool> &vis, vector<int>&compo, vector<int> &compo_id, int id, vector<vector<int>> &tg) {
    vis[u] = true;
    compo.push_back(u);
    for (auto v : tg[u]) {
        if (!vis[v]) dfs2(v, compo);
    }
}
void scc(vector<vector<int>> &g, vector<vector<int>> &tg, int n) {
    vector<bool> vis(n + 1);
    vector<int> topo;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i, vis, topo, g); // build topo based on out_time
        }
    }
    reverse(all(topo));
    fill(all(vis), false);
    compo_id.resize(n + 1);
    int id = 1;
    for (auto u : topo) {
        if (!vis[u]) {
            vector<int> compo;
            dfs2(u, vis, compo, compo_id, id, tg); // build each compo from transpose graph, the largest out_time compo will be marked first
            for (auto x : compo) compo_id[x] = id;
            compos.emplace_back(compo);
            id++;
        }
    }
    for (int u = 1; u <= n; u++) { // build bridges and condensed graph
        for (auto v : g[u]) {
            if (compo_id[u] != compo_id[v]) {
                bridges.push_back({u,v});
                cg[compo_id[u]].push_back({compo_id[v]});
            }
        }
    }
    
}

int main() {
    scc(g, tg, n);
    // then use cg, bridges,..
}
