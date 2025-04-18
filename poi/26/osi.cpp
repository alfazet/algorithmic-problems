#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e6 + 3;

vector <pair <int, int>> adj[MAXN];
pair <int, int> edges[MAXN];
bool used[MAXN]; 
int pre[MAXN], low[MAXN], timer = 1, bridges = 0;
char orient[MAXN]; // tree-edges oriented with DFS, back-edges against DFS

void DFS(int v){
    pre[v] = low[v] = timer++;
    for (auto[child, id] : adj[v]){
        if (!used[id]){
            used[id] = true;
            orient[id] = (edges[id].first == v ? '>' : '<');
            if (pre[child] == 0){
                DFS(child);
                low[v] = min(low[v], low[child]);
                if (low[child] > pre[v]){
                    bridges++;
                }
            }
            else{
                low[v] = min(low[v], pre[child]);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, a, b, ccs = 0;
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a].emplace_back(b, i);
        adj[b].emplace_back(a, i);
        edges[i] = {a, b};
    }
    for (int i = 1; i <= n; i++){
        if (!pre[i]){
            ccs++;
            DFS(i);
        }
    }

    cout << ccs + bridges << "\n";
    for (int i = 0; i < m; i++){
        cout << orient[i];
    }
    cout << "\n";

    return 0;
}   
