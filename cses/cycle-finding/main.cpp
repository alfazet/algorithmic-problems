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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, u, v, w;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<edge_t> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        edges[i] = {u, v, w};
    }
    vector<int64_t> dist(n + 1, INF), new_dist(n + 1, INF), prev(n + 1, -1);
    dist[1] = 0;
    int changed_v = -1;
    // a negative cycle exists <=> any distance decreased in the "additional" (n-th) iteration
    for (int i = 0; i < n; i++) {
        new_dist = dist;
        for (auto& [u, v, w] : edges) {
            if (dist[v] > dist[u] + w) {
                new_dist[v] = dist[u] + w;
                prev[v] = u;
                if (i == n - 1) {
                    changed_v = v;
                }
            }
        }
        dist = new_dist;
    }
    if (changed_v == -1) {
        cout << "NO\n";
        return 0;
    }

    vector<int> back_path;
    int x = changed_v, cycle_start = -1;
    vector<bool> vis(n + 1);
    for (int i = 0; i < n + 1; i++) {
        if (vis[x]) {
            back_path.push_back(x);
            cycle_start = x;
            break;
        }
        vis[x] = true;
        back_path.push_back(x);
        x = prev[x];
    }
    cout << "YES\n";
    int start_visits = 0;
    for (auto it = back_path.rbegin(); it != back_path.rend(); it++) {
        if (*it == cycle_start) {
            start_visits++;
        }
        cout << *it << ' ';
        if (start_visits == 2) {
            break;
        }
    }
    cout << '\n';

    return 0;
}
