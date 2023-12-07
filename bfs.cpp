#include <bits/stdc++.h>
using namespace std;

string printPathTo(int vertice, vector<int>& path);

int main() {
    vector<vector<int>> edges = {{1,2}, {1,3}, {3,4}};
    unordered_map<int,vector<int>> g;
    for (auto edge : edges) {
        g[edge[0]].push_back(edge[1]);
        g[edge[1]].push_back(edge[0]);
    }

    vector<int> visited(g.size() + 1, false);
    vector<int> dist(g.size() + 1, 0);
    vector<int> path(g.size() + 1, -1);

    deque<int> q;
    q.push_front(1);
    visited[1] = true;
    
    while (q.size()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            int u = q.back(); q.pop_back();

            for (auto v : g[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push_front(v);

                    dist[v] = dist[u] + 1;
                    path[v] = u;
                }
            }
        }
    }

    cout << printPathTo(4, path);

    return 0;
}

string printPathTo(int vertice, vector<int>& path) {
    vector<int> v;
    v.push_back(vertice);
    int cur = path[vertice];
    while (cur != -1) {
        v.push_back(cur);
        cur = path[cur];
    }
    reverse(v.begin(), v.end());
    string res = "";
    for (int i = 0; i < v.size(); i++) {
        res += to_string(v[i]);
        if (i != v.size() - 1) res += " -> ";
    }
    return res;
}