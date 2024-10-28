#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int,int>>> g;
void bellman(int s) {
    int n; // vertices
    vector<int> dist(n, INT_MAX);

    // Run first n-1 loop to relax as much as possible
    dist[s] = 0;
    bool stopEarly = false;
    for (int i = 1; i < n - 1; i++) {
        bool atLeast1 = false;
        for (int u = 0; u < n; u++) {
            for (auto &nei : g[u]) {
                int v = nei.first;
                int w_uv = nei.second;
                if (dist[u] != INT_MAX && dist[u] + w_uv < dist[v]) {
                    dist[v] = dist[u] + w_uv;
                    atLeast1 = true;
                }    
            }
        }
        if (!atLeast1) {stopEarly = true; break;} // can not relax any edge
    }
    if (stopEarly) return; // stop early => no negative cyclce

    // Check negative cycle, and mark vertices affected by negative cycle
    // Any vertice can be relaxed from n loop => Affected by the negative cycle
    // All vertices affected marked by dist <= INT_MIN
    for (int i = 1; i <= n; i++) {
        for (int u = 0; u < n; u++) {
            for (auto &nei : g[u]) {
                int v = nei.first;
                int w_uv = nei.second;
                if (dist[u] != INT_MAX && dist[u] + w_uv < dist[v]) {   // care overflow here
                    dist[v] = INT_MIN;
                }
            }
        }
    }
}

int main() {
    return 0;
}