#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int K = 203, MAXN = 1e5 + 3, INF = 1e9 + 3;

vector <int> adj[MAXN];
int d[K][MAXN]; // dist[i][v] - dist from i-th random vertex to v

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q, a, b;
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int k = min(200, n);

    srand(2137);
    vector <int> r(n);
    iota(r.begin(), r.end(), 1);
    random_shuffle(r.begin(), r.end());
    for (int i = 0; i < k; i++){
        for (int v = 1; v <= n; v++){
            d[i][v] = INF;
        }
        queue <int> q;
        q.push(r[i]);
        d[i][r[i]] = 0;
        while (!q.empty()){
            int v = q.front();
            q.pop();
            for (int child : adj[v]){
                if (d[i][child] == INF){
                    d[i][child] = d[i][v] + 1;
                    q.push(child);
                }
            }
        }
    }

    while (q--){
        cin >> a >> b;
        int ans = INF;
        for (int i = 0; i < k; i++){
            ans = min(ans, d[i][a] + d[i][b]);
        }
        cout << ans << "\n";
    }

    return 0;
}   
