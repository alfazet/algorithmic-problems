#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 3e4 + 3, LOG = 15;

vector <int> adj[MAXN];
int up[MAXN][LOG], depth[MAXN];

void DFS(int v, int par, int dep){
	depth[v] = dep;
	up[v][0] = par;
	for (int child : adj[v]){
		if (child != par){
			DFS(child, v, dep + 1);
		}
	}
}

int LCA(int u, int v){
	if (depth[u] < depth[v]){
		swap(u, v);
	}
	int d = depth[u] - depth[v];
	for (int b = 0; b < LOG; b++){
		if (d & (1 << b)){
			u = up[u][b];
		}
	}
	
	if (u == v){
		return u;
	}
	
	for (int b = LOG - 1; b >= 0; b--){
		if (up[u][b] != up[v][b]){
			u = up[u][b];
			v = up[v][b];
		}
	}
	return up[u][0];
}

int dist(int u, int v){
	return depth[u] + depth[v] - 2 * depth[LCA(u, v)];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	int n, q, a, b, v;
	cin >> n;
	for (int i = 0; i < n - 1; i++){
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	DFS(1, 0, 0);
	for (int b = 1; b < LOG; b++){
		for (int i = 1; i <= n; i++){
			up[i][b] = up[up[i][b - 1]][b - 1];
		}
	}
	
	int ans = 0, prev = 1;
	cin >> q;
	while (q--){
		cin >> v;
		ans += dist(prev, v);
		prev = v;
	}
	cout << ans << "\n";
	
    return 0;
}
