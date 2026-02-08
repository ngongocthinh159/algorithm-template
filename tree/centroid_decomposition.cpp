/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/2080/
*/

#include<bits/stdc++.h>
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9)
#define MASK(i) (1LL << (i))
#define all(v) (v).begin(), (v).end()


template<class X, class Y>
bool minimize(X &x, const Y &y) {
    if (x > y) {
        x = y;
        return true;
    } else return false;
}
template<class X, class Y>
bool maximize(X &x, const Y &y) {
    if (x < y) {
        x = y;
        return true;
    } else return false;
}

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("Input.txt", "r", stdin);
freopen("Output.txt", "w", stdout);
#endif
}
struct chash {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(uint64_t x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x + FIXED_RANDOM);}}; // https://codeforces.com/blog/entry/62393
struct chashp {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(pair<uint64_t,uint64_t> x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);}}; // https://codeforces.com/blog/entry/62393
/*--------------------------------------------------------------------------------------------------------------------------*/

// problem: given a tree, count all paths have number of edges = exactly k

#define N 200005
int n, k;
vector<int> g[N];
int child[N], mxd;
bool del[N];
ll f[N], ans = 0;
void pre_compute() {
    
}
int dfs(int u, int p) {
    child[u] = 1;
    for (auto v : g[u]) if (v != p && !del[v]) child[u] += dfs(v, u);
    return child[u];
}
int find_centroid(int u, int p, int sz) {
    for (auto v : g[u]) if (v != p && !del[v] && child[v] > sz/2)
        return find_centroid(v, u, sz);
    return u;
}
void acc_ans(int u, int p, int d) {
    if (d > k) return;
    mxd = max(mxd, d);
    ans += f[k - d];
    for (auto v : g[u]) if (v != p && !del[v])
        acc_ans(v, u, d + 1);
}
void merge_subtree(int u, int p, int d) {
    if (d > k) return;
    f[d]++;
    for (auto v : g[u]) if (v != p && !del[v])
        merge_subtree(v, u, d + 1);
}
void CD(int u) {
    // step 1: find centroid
    dfs(u, -1);
    u = find_centroid(u, -1, child[u]);

    // step 2: find ans go through current centroid
    // For each subtree accumulate ans, then merge subtree
    mxd = -1;
    f[0] = 1; // merge_subtree root
    for (auto v : g[u]) if (!del[v]) {
        acc_ans(v, u, 1);
        
        merge_subtree(v, u, 1);
    }
    for (int i = 0; i <= mxd; i++) f[i] = 0; // clear local state of this centroid component

    // step 3: recursive solve for paths not go through current centroid
    del[u] = 1;
    for (auto v : g[u]) if (!del[v]) 
        CD(v);
}
void solve() {
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    CD(1);
    cout << ans << nline;
}

int main() {
    fastio();
    IN_OUT();
    int T = 1;
    // cin >> T;
    pre_compute();
    for (int cases = 1; cases <= T; cases++) {

        solve();
    }
    return 0;
}