#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e5 + 3;

pair <int, int> back_edge;
vector <int> adj[MAXN];
bool vis[MAXN];
int ans[MAXN];

void DFS_find_back_edge(int v, int par){
    vis[v] = true;
    for (int child : adj[v]){
        if (child != par){
            if (!vis[child]){
                DFS_find_back_edge(child, v);
            }
            else if (back_edge == pair{0, 0}){
                back_edge = {v, child};
            }
        }
    }
}

void DFS_find_matching(int v, int par){
    for (int child : adj[v]){
        if (child != par){
            if (ans[child] == 0){
                ans[child] = v;
                DFS_find_matching(child, v);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int n, m, a, b;
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= n; i++){
        if (!vis[i]){
            back_edge = {0, 0};
            DFS_find_back_edge(i, 0);
            if (back_edge == pair{0, 0}){
                cout << "NIE\n";
                return 0;
            }

            auto[u, v] = back_edge;
            for (int j = 0; j < (int) adj[u].size(); j++){
                if (adj[u][j] == v){
                    swap(adj[u][j], adj[u].back());
                    adj[u].pop_back();
                    break;
                }
            }
            for (int j = 0; j < (int) adj[v].size(); j++){
                if (adj[v][j] == u){
                    swap(adj[v][j], adj[v].back());
                    adj[v].pop_back();
                    break;
                }
            }

            DFS_find_matching(v, 0);
            ans[v] = u;
        }
    }
    cout << "TAK\n";
    for (int i = 1; i <= n; i++){
        cout << ans[i] << "\n";
    }

    return 0;
}   
