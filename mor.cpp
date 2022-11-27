//XX OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int maxn = 5003, maxq = 1e6 + 3, INF = 1e9 + 3;
int n;

struct query{
    int dest;
    int len;
    int id;
};

bool ans[maxq];
vector <int> adj[2 * maxn];
int dist[2 * maxn];
vector <query> queries[maxn];

void BFS(int v){
    for (int i = 1; i <= 2 * n; i++){
        dist[i] = INF;
    }
    queue <int> q;
    q.push(v);
    dist[v] = 0;
    int cur;
    while (!q.empty()){
        cur = q.front();
        q.pop();
        for (int child : adj[cur]){
            if (dist[child] == INF){
                dist[child] = dist[cur] + 1;
                q.push(child);
            }
        }
    }
}

void solve(){
    int m, q, a, b, l, end_v;
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a].push_back(b + n);
        adj[b].push_back(a + n);
        adj[a + n].push_back(b);
        adj[b + n].push_back(a);
    }
    for (int i = 0; i < q; i++){
        cin >> a >> b >> l;
        queries[a].push_back({b, l, i});
    }
    for (int i = 1; i <= n; i++){
        BFS(i);
        if (!adj[i].empty() && !queries[i].empty()){
            for (query qu : queries[i]){
                end_v = qu.dest;
                if (qu.len % 2 == 1){
                    end_v += n;
                }
                if (dist[end_v] != INF && dist[end_v] <= qu.len){
                    ans[qu.id] = true;
                }
            }
        }
    }
    for (int i = 0; i < q; i++){
        cout << (ans[i] ? "TAK\n" : "NIE\n");
    }
}

int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    t = 1;
    //cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
