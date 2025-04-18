#include <iostream>
#include <queue>
#include <utility>
#include <vector>
 
using namespace std;
 
constexpr int64_t INF = 1e18 + 9;
 
typedef struct edge_t {
    int u, v;
    int64_t w;
} edge_t;
 
vector<int64_t> dijkstra(int src, vector<vector<pair<int, int>>> &adj) {
    vector<int64_t> dist(adj.size() + 1, INF);
 
    priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<pair<int64_t, int>>> pq;
    pq.emplace(0, src);
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (dist[v] == INF) {
            dist[v] = d;
            for (auto &[u, w] : adj[v]) {
                if (dist[u] > d + w) {
                    pq.emplace(d + w, u);
                }
            }
        }
    }
    return dist;
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    int n, m, u, v;
    int64_t w;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n + 1), adj_t(n + 1);
    vector<edge_t> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj_t[v].emplace_back(u, w);
        edges[i] = {u, v, w};
    }
    auto dist = dijkstra(1, adj);
    auto dist_t = dijkstra(n, adj_t);
    int64_t ans = INF;
    for (auto &[u, v, w] : edges) {
        ans = min(ans, dist[u] + w / 2 + dist_t[v]);
    }
    cout << ans << '\n';
 
    return 0;
}
