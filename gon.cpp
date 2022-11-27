//V OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int maxn = 3004;

vector <int> adj[maxn];
bool vis[maxn], safe[maxn];
int dist[maxn][2], in[maxn], low[maxn];
int timer;

void BFS(int v, int iter){
    queue <int> q;
    q.push(v);
    dist[v][iter] = 0;
    while (!q.empty()){
        v = q.front();
        q.pop();
        vis[v] = true;
        for (int child : adj[v]){
            if (!vis[child]){
                dist[child][iter] = dist[v][iter] + 1;
                q.push(child);
            }
        }
    }
}

int DFS(int v, int par){
    timer++;
    in[v] = low[v] = timer;
    vis[v] = true;
    for (int child : adj[v]){
        if (child != par){
            if (vis[child]){
                low[v] = min(low[v], in[child]);
            }
            else{
                DFS(child, v);
                low[v] = min(low[v], low[child]);
                if (low[v] < in[v]){
                    safe[v] = true;
                }
            }
        }
    }
    return low[v];
}

void solve(){
    int n, m, A, B, a, b;
    cin >> n >> m >> A >> B;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    BFS(A, 0);
    memset(vis, false, sizeof(vis));
    BFS(B, 1);
    memset(vis, false, sizeof(vis));
    DFS(1, -1);
    int ans = 0;
    for (int i = 1; i <= n; i++){
        if (safe[i]){
            if (dist[i][0] < dist[i][1]){
                cout << "NIE\n";
                return;
            }
        }
        if (dist[i][0] <= dist[i][1]){
            ans = max(ans, dist[i][1]);
        }
    }
    cout << ans << "\n";
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
