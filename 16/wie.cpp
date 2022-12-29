#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const int INF = 1e9 + 3;

struct Edge{
    int v, w, mask;

    Edge(int v_, int w_, int mask_) : v(v_), w(w_), mask(mask_) {};
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int a, b, w, n, m, p, k, v, c, x;
    cin >> n >> m >> p >> k;

    vector <int> swords(n + 1);
    vector <vector <Edge>> adj(n + 1);

    for (int i = 0; i < k; i++){
        cin >> v >> c;
        for (int j = 0; j < c; j++){
            cin >> x;
            x--;
            swords[v] |= (1 << x);
        }
    }
    for (int i = 0; i < m; i++){
        cin >> a >> b >> w >> c;
        adj[a].emplace_back(b, w, 0);
        adj[b].emplace_back(a, w, 0);
        for (int j = 0; j < c; j++){
            cin >> x;
            x--;
            adj[a].back().mask |= (1 << x);
            adj[b].back().mask |= (1 << x);
        }
    }

    priority_queue <pair <int, pair <int, int>>, vector <pair <int, pair <int, int>>>, greater <pair <int, pair <int, int>>>> pq; // state {vertex, mask}
    vector <vector <int>> dist(n + 1, vector <int>(1 << p, INF));
    pq.emplace(0, pair{1, 0});
    dist[1][0] = 0;

    auto is_submask = [&](int mask, int sub){
        return (mask & sub) == sub;
    };

    while (!pq.empty()){
        auto[d, v] = pq.top();
        pq.pop();

        int new_mask = v.ss | swords[v.ff];
        for (auto[child, w, monsters] : adj[v.ff]){
            if (is_submask(new_mask, monsters) && dist[child][new_mask] > dist[v.ff][v.ss] + w){
                dist[child][new_mask] = dist[v.ff][v.ss] + w;
                pq.emplace(dist[child][new_mask], pair{child, new_mask});
            }
        }
    }

    int ans = INF;
    for (int mask = 0; mask < (1 << p); mask++){
        ans = min(ans, dist[n][mask]);
    }
    cout << (ans == INF ? -1 : ans) << "\n";

    return 0;
}   
