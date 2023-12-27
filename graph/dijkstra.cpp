#include <bits/stdc++.h>
using namespace std;

/**
 * Không trace path
*/
struct comparator {
  bool operator() (const pair<int,int> &a, const pair<int,int> &b) const {
    if (b.second < a.second) return true;
    return false;
  }
};
void shortestPath(int s, vector<vector<pair<int,int>>>& g, vector<int> &dist) {
    // setup
    dist = vector<int>(g.size() + 1, INT_MAX);
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
            if (w + w_uv < dist[v]) {
                dist[v] = w + w_uv;
                pq.push({v, dist[v]});
            }
        }
    }
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