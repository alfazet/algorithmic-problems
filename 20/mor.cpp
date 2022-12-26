#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 5e3 + 3, INF = 1e9 + 3;

vector <int> adj[2 * MAXN];
int n, dist[2 * MAXN];

void BFS(int v){
    for (int i = 1; i <= n; i++){
        dist[i] = INF;
        dist[i + MAXN] = INF;
    }

    dist[v] = 0;
    queue <int> q;
    q.push(v);

    while (!q.empty()){
        v = q.front();
        q.pop();
        for (int child : adj[v]){
            if (dist[child] == INF){
                dist[child] = dist[v] + 1;
                q.push(child);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int m, a, b, q, u, v, len;
    cin >> n >> m >> q;
    vector <vector <tuple <int, int, int>>> queries(n + 1);
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a].push_back(b + MAXN);
        adj[b + MAXN].push_back(a);
        adj[b].push_back(a + MAXN);
        adj[a + MAXN].push_back(b);
    }

    for (int i = 0; i < q; i++){
        cin >> u >> v >> len;
        queries[u].emplace_back(v, len, i);
    }

    vector <bool> ans(q);
    for (int i = 1; i <= n; i++){
        BFS(i);
        for (auto[v, len, id] : queries[i]){
            ans[id] = (!adj[i].empty() && dist[v + (len % 2) * MAXN] <= len);
        }
    }

    for (int i = 0; i < q; i++){
        cout << (ans[i] ? "TAK\n" : "NIE\n");
    }

    return 0;
}   
