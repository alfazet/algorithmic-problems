#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 3e5 + 3, MAXW = 1e5 + 3;

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

vector <Edge> edges[MAXW];
int ans[MAXN];

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
			if (u != v){ // this edge could've been the first of this weight and it would've been picked to the MST
				ans[i] = 1;
			}
		}
		for (auto [u, v, w, i] : edges[w]){ // we connect with the edges that are in some MST
			u = ds.find(u);
			v = ds.find(v);
			if (ans[i] != 0){ 
				ds.merge(u, v);
			}
		}
	}
	
	for (int i = 0; i < m; i++){
		cout << (ans[i] ? "TAK\n" : "NIE\n");
	}

    return 0;
}   
