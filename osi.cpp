//XXVI OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e6 + 3;

vector <pair <int, int>> adj[MAXN];
pair <int, int> edges[MAXN];
bool vis[MAXN], used[MAXN], orient[MAXN];
int pre[MAXN], low[MAXN], ccs = 0, timer = 1, bridges = 0;

void DFS(int v){
	pre[v] = low[v] = timer++;
	for (auto [child, id] : adj[v]){
		if (!used[id]){
			used[id] = true;
			orient[id] = (edges[id].second == child);
			if (pre[child] == 0){ // tree-edge
				DFS(child);
				low[v] = min(low[v], low[child]);
				if (low[child] > pre[v]){ // nie ma żadnego back-edga z dołu
					bridges++;
				}
			}
			else{ // back-edge
				low[v] = min(low[v], low[child]);
			}
		}
	}
}

void DFS_cc(int v){
    vis[v] = true;
    for (auto [child, id] : adj[v]){
        if (!vis[child]){
            DFS_cc(child);
        }
    }
}

void solve(){
    int n, m, a, b;
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a].emplace_back(b, i);
        adj[b].emplace_back(a, i);
        edges[i] = {a, b};
    }
    for (int i = 1; i <= n; i++){
        if (!pre[i]){
            DFS(i);
        }
    }
    for (int i = 1; i <= n; i++){
        if (!vis[i]){
            DFS_cc(i);
            ccs++;
        }
    }
    cout << ccs + bridges << "\n";
    for (int i = 0; i < m; i++){
        cout << (orient[i] ? '>' : '<');
    }
    cout << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    //cin >> t;
    while (t--){
        solve();
    }
    return 0;
}   
