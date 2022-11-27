//XV OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int maxn = 1e5 + 3;
vector <int> adj[maxn];
int vis[maxn], ans[maxn];

pair <int, int> special;
int timer = 0;
bool found_cycle;

void DFS(int v, int par){
    vis[v] = timer;
    for (int child : adj[v]){
        if (child != par){
            if (vis[child] == timer){
                special.first = v;
                special.second = child;
                found_cycle = true;
            }
            else{
                ans[child] = v;
                DFS(child, v);
            }
        }
    }
}

void solve(){
    int n, m, a, b, u, v;
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= n; i++){
        if (ans[i] == 0){
            found_cycle = 0;
            timer++;
            DFS(i, -1);
            u = special.first;
            v = special.second;
            if (!found_cycle){
                cout << "NIE\n";
                return;
            }
            else{
                for (int j = 0; j < adj[u].size(); j++){
                    if (adj[u][j] == v){
                        swap(adj[u][j], adj[u].back());
                    }
                }
                for (int j = 0; j < adj[v].size(); j++){
                    if (adj[v][j] == u){
                        swap(adj[v][j], adj[v].back());
                    }
                }
                adj[u].pop_back();
                adj[v].pop_back();
                timer++;
                ans[u] = v;
                DFS(u, -1);
            }
        }
    }
    cout << "TAK\n";
    for (int i = 1; i <= n; i++){
        cout << ans[i] << "\n";
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
