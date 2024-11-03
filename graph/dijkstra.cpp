#include <bits/stdc++.h>
using namespace std;

/**
 * Không trace path
*/
vector<ll> dijkstra(int src, vector<vector<pair<int,ll>>>& g, int n) {
    vector<ll> dist(n + 1, LINF);
    set<pair<ll,int>> S;
    S.insert({0,src});
    dist[src] = 0;
    
    while (S.size()) {
        auto p = *S.begin();
        S.erase(S.begin());
        int u = p.second;
        int w_u = p.first;

        for (auto _p : g[u]) {
            int v = _p.first;
            int w_uv = _p.second;
            if (dist[v] > w_u + w_uv) {
                S.erase({dist[v], v});
                dist[v] = w_u + w_uv;
                S.insert({dist[v], v});
            }
        }
    }
    return dist;
}




/**
 * Có trace path
*/
struct comparator {
  bool operator() (const pair<int,int> &a, const pair<int,int> &b) const {
    if (b.second < a.second) return true;
    return false;
  }
};
void shortestPath(int s, vector<vector<pair<int,int>>>& g, vector<int> &dist, vector<vector<int>> &path) {
    // setup
    dist = vector<int>(g.size() + 1, INT_MAX);
    path = vector<vector<int>(g.size() + 1);
    priority_queue<pair<int,int>, vector<pair<int,int>>, comparator > pq; // min pq
    
    pq.push({s, 0});
    dist[s] = 0;
    while (pq.size()) {
        auto best = pq.top(); pq.pop();
        int u = best.first;
        int w = best.second;

        for (auto nei : g[u]) {
            int v = nei.first;
            int w_uv = nei.second;
            if (w + w_uv <= dist[v]) {
                if (w + w_uv < dist[v]) {
                    dist[v] = w + w_uv;
                    pq.push({v, dist[v]});

                    path[v].clear();    // find new shortest path => clear all old vertices
                }
                path[v].push_back(u);   // push vertices with same shortest path
            }
        }
    }
}
void trace(int v) {
    for (auto &u : path[v]) {
        // do something with path
        trace(u);
    }
}


int main() {
    return 0;
}