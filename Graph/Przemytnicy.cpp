//X OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const int MAXN = 1e5 + 3;
const lli INF = 1e18 + 3;

lli dist[2 * MAXN + 7];
vector <pair <int, lli>> adj[2 * MAXN + 7];

void Dijkstra(int v){
    priority_queue <pair <lli, int>> pq;
    pq.push({0, v});
    dist[v] = 0;
    int so_far;
    while (!pq.empty()){
        v = pq.top().ss;
        so_far = -pq.top().ff;
        pq.pop();
        for (auto p : adj[v]){
            if (dist[p.ff] > so_far + p.ss){
                pq.push({-(so_far + p.ss), p.ff});
                dist[p.ff] = so_far + p.ss;
            }
        }
    }
}

void solve(){
	int n, m, a, b, w, price;
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> price;
        adj[i].emplace_back(i + MAXN, price / 2);
        dist[i] = INF;
        dist[i + MAXN] = INF;
    }
    cin >> m;
    for (int i = 0; i < m; i++){
        cin >> a >> b >> w;
        adj[a].emplace_back(b, w);
        adj[a + MAXN].emplace_back(b + MAXN, w);
    }
    Dijkstra(1);
    cout << dist[1 + MAXN] << "\n";
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	int t;
	t = 1;
	//cin >> t;
	while (t--){
		solve();
	}
	return 0;
}
