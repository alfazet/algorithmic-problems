//XVII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std; 

const int maxn = 2e5 + 3;

vector <int> adj[maxn];
bool vis[maxn];
int color[maxn];

void dfs(int node, int cl){
	vis[node] = true;
	if (color[node] == 0){
		color[node] = cl;	
	}
	
	for (int child : adj[node]){
		if (!vis[child]){
			dfs(child, (cl == 1 ? 2 : 1));
		}
	}
}

void solve(){
	int n, m, a, b;
	cin >> n >> m;
	for (int i = 0; i < m; i++){
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (int i = 1; i <= n; i++){
		if (adj[i].empty()){
			cout << "NIE\n";
			return;
		}
		if (!vis[i]){
			dfs(i, 1);
		}
	}
	cout << "TAK\n";
	for (int i = 1; i <= n; i++){
		cout << (color[i] == 1 ? "K\n" : "S\n");
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
