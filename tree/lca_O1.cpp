#include <bits/stdc++.h>
using namespace std;

#define LOG 20
#define MAX 100005
#define MASK(x) (1 << x)
#define RELAX(x, y) (height[x] < height[y] ? (x) : (y))

int height[MAX];
int cnt = -1; // index of last element in euler tour
int euler[2*MAX]; // euler size = 2*n - 1 elements, each element of euler tour is vertice number
int pos[2*MAX]; // pos[u] is index of u in euler tour
vector<int> g[MAX];
int minHeight[LOG + 1][2*MAX]; // rmq min height in range
void dfs(int u, int par) {
    euler[++cnt] = u;
    pos[u] = cnt;
    for (auto v : g[u]) {
        if (v != par) {
            height[v] = height[u] + 1;
            dfs(v, u);
            euler[++cnt] = u;
        }
    }
}
void preprocess_rmq() {
    for (int i = 0; i <= cnt; i++) minHeight[0][i] = height[euler[i]];
    for (int j = 1; j <= LOG; j++)
        for (int i = 0; i <= cnt; i++)
            if (i + MASK(j) - 1 <= cnt) {
                minHeight[j][i] = RELAX(minHeight[j - 1][i], minHeight[j - 1][i + MASK(j - 1)]);
            } else break;
}
int query_rmq(int l, int r) {
    int msb = 32 - __builtin_clz(r - l + 1) - 1;
    return RELAX(minHeight[msb][l], minHeight[msb][r - MASK(msb) + 1]);
}
int query_lca(int u, int v) {
    if (pos[u] > pos[v]) swap(u, v);
    return query_rmq(pos[u], pos[v]);
}

int n;
void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // build euler tour
    dfs(1, -1);

    preprocess_rmq();

    cout << query_lca(1, 4);
}

int main() {
    solve();

    return 0;
}
