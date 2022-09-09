//XXVI OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const int MAXN = 1e6 + 3;

int ccs = 0, timer = 1, bridges = 0;
vector <pair <int, int>> adj[MAXN];
char orient[MAXN];
pair <int, int> edges[MAXN];
bool used_edge[MAXN];
int in[MAXN], low[MAXN];
bool vis[MAXN];

void DFS_tree(int v){
    int u, id;
    in[v] = low[v] = timer++;
    for (pair <int, int> child : adj[v]){
        u = child.ff;
        id = child.ss;
        if (used_edge[id]){
            continue;
        }
        used_edge[id] = true;
        orient[id] = (u == edges[id].ss ? '>' : '<');
        if (!in[u]){
            DFS_tree(u);
            low[v] = min(low[v], low[u]);
            if (low[u] > in[v]){
                bridges++;
            }
        }
        else{
            low[v] = min(low[v], low[u]);
        }
    }
}

void DFS(int v){
    vis[v] = true;
    for (pair <int, int> child : adj[v]){
        if (!vis[child.ff]){
            DFS(child.ff);
        }
    }
}

void solve(){
    int n, m, a, b;
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
        edges[i] = {a, b};
    }
    for (int i = 1; i <= n; i++){
        if (!in[i]){
            DFS_tree(i);
        }
    }
    for (int i = 1; i <= n; i++){
        if (!vis[i]){
            DFS(i);
            ccs++;
        }
    }
    cout << ccs + bridges << "\n";
    for (int i = 0; i < m; i++){
        cout << orient[i];
    }
    cout << "\n";
}

int main(){
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
