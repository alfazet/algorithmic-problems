#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e5 + 3, MAXW = 1e6 + 3;

struct DSU{
	int n;
	vector <int> par, sz;
	
	DSU(int n_) : n(n_) {
		par.resize(n + 1);
		sz.resize(n + 1);
		
		for (int i = 1; i <= n; i++){
			par[i] = i;
			sz[i] = 1;
		}
	};
	
	int find(int x){
		if (x == par[x]){
			return x;
		}
		return par[x] = find(par[x]);
	}
	
	void merge(int u, int v){
		u = find(u);
		v = find(v);
		if (u == v){
			return;
		}
		if (sz[v] < sz[u]){
			swap(u, v);
		}
		sz[v] += sz[u];
		par[u] = v;
	}
};

struct Edge{
	int u, v, w, i;
	
	Edge(int u_, int v_, int w_, int i_) : u(u_), v(v_), w(w_), i(i_) {};
	
	bool operator <(const Edge &e){
		return w < e.w;
	}
};

vector <Edge> adj[MAXN], edges[MAXW];
int ans[MAXN], pre[MAXN], low[MAXN], timer = 1;
bool used[MAXN];

void DFS(int v){
	pre[v] = low[v] = timer++;
	for (auto [v, child, w, i] : adj[v]){
		if (!used[i]){
			used[i] = true;
			if (pre[child] == 0){
				DFS(child);
				low[v] = min(low[v], low[child]);
				if (low[child] > pre[v]){
					ans[i] = 2; // a bridge
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

	int n, m, a, b, w;
	cin >> n >> m;
	for (int i = 0; i < m; i++){
		cin >> a >> b >> w;
		edges[w].emplace_back(a, b, w, i);
	}
	
	DSU ds(n);
	for (int w = 1; w < MAXW; w++){
		for (auto [u, v, w, i] : edges[w]){
			u = ds.find(u);
			v = ds.find(v);
			if (u != v){ // this edge could've been the first of this weight and it would've been picked to the MST - so we add its CC to the graph
				adj[u].emplace_back(u, v, w, i);
				adj[v].emplace_back(v, u, w, i);
				ans[i] = 1;
			}
		}
		for (auto [u, v, w, i] : edges[w]){ // DFS on a graph of CCs where edge weight == w. An edge is in any MST iff it's a bridge in this graph, since later edges will only be heavier.
			u = ds.find(u);
			if (pre[u] == 0){
				DFS(u);
			}
		}
		for (auto [u, v, w, i] : edges[w]){ // we connect CCs with the edges that are in some MST
			u = ds.find(u);
			v = ds.find(v);
			adj[u].clear();
			adj[v].clear();
			pre[u] = pre[v] = low[u] = low[v] = 0;
			used[i] = false;
			if (ans[i] != 0){
				ds.merge(u, v);
			}
		}
		timer = 1;
	}
	
	string text[3] = {"none", "at least one", "any"};
	for (int i = 0; i < m; i++){
		cout << text[ans[i]] << "\n";
	}

    return 0;
}   
