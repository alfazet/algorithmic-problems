#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef long long int lli;

constexpr int MAX_N = 503, MAX_M = 1003;
constexpr lli INF = 9e18 + 9;

vector<int> adj[MAX_N];
lli cap[MAX_N][MAX_N];
bool s_part[MAX_M];

int find_augmenting_path(int s, int t, vector<int>& prev) {
    fill(prev.begin(), prev.end(), -1);
    prev[s] = 0;
    queue<pair<int, lli>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int v = q.front().first;
        lli flow = q.front().second;
        q.pop();
        for (int u : adj[v]) {
            if (prev[u] == -1 && cap[v][u] != 0) {
                prev[u] = v;
                lli new_flow = min(flow, cap[v][u]);
                if (u == t) {
                    return new_flow;
                }
                q.push({u, new_flow});
            }
        }
    }
    return 0;
}

lli find_max_flow(int s, int t, int n) {
    lli max_flow = 0, new_flow;
    vector<int> prev(n + 1);
    while ((new_flow = find_augmenting_path(s, t, prev)) > 0) {
        max_flow += new_flow;
        int v = t;
        while (v != s) {
            int u = prev[v];
            cap[u][v] -= new_flow;
            cap[v][u] += new_flow;
            v = u;
        }
    }
    return max_flow;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, u, v;
    lli w;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        adj[u].push_back(v);
        adj[v].push_back(u);
        cap[u][v] += w;
    }
    cout << find_max_flow(1, n, n) << '\n';

    return 0;
}
