#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e5 + 3, SQRT = 317;

vector <pair <int, int>> adj[MAXN];
pair <int, int> edges[MAXN];
vector <int> freq[SQRT + 1];
int typ[MAXN], big_id[MAXN], normal_id[MAXN], parent[MAXN], edge_to_par[MAXN], cnt[SQRT + 1], pre[MAXN], post[MAXN], timer, cnt_big;

int DFS(int v, int par, int dep, int distinct, int e_id, vector <int> &f){
	pre[v] = timer++;
	parent[v] = par;
	edge_to_par[v] = e_id;
	bool nowy = false;
	int deepest_path = 0;
	
	for (auto [u, id] : adj[v]){
		if (u != par){
			f[typ[id]]++;
			if (f[typ[id]] == 1){
				nowy = true;
			}
			deepest_path = max(deepest_path, DFS(u, v, dep + 1, distinct + nowy, id, f) + 1);
			f[typ[id]]--;
		}
	}
	
	if (dep % SQRT == 0 && deepest_path >= SQRT){
		big_id[v] = ++cnt_big;
		normal_id[big_id[v]] = v;
		freq[big_id[v]] = f;
		cnt[big_id[v]] = distinct;
	}
	
	post[v] = timer++;
	return deepest_path;
}

int query(int v){
	set <int> seen;
	while (parent[v] != -1 && big_id[v] == 0){
		seen.insert(typ[edge_to_par[v]]);
		v = parent[v];
	}
	
	if (parent[v] == -1){
		return seen.size();
	}
	
	int ans = cnt[big_id[v]];
	for (int b : seen){
		if (freq[big_id[v]][b] == 0){
			ans++;
		}
	}
	return ans;
}

void update(int id, int nowy){
	int stary = typ[id];
	typ[id] = nowy;
	auto[u, v] = edges[id];
	if (parent[u] == v){
		swap(u, v); // v głębiej
	}
	for (int i = 1; i <= cnt_big; i++){
		int big = normal_id[i];
		if (pre[big] >= pre[v] && post[big] <= post[v]){
			freq[i][stary]--;
			if (freq[i][stary] == 0){
				cnt[i]--;
			}
			freq[i][nowy]++;
			if (freq[i][nowy] == 1){
				cnt[i]++;
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m, q, a, b, t, v, id, x;
	char c;
	cin >> n >> m >> q;
	for (int i = 1; i < n; i++){
		cin >> a >> b >> t;
		adj[a].emplace_back(b, i);
		adj[b].emplace_back(a, i);
		typ[i] = t;
		edges[i] = {a, b};
	}
	vector <int> f(m + 1);
	DFS(1, -1, 0, 0, -1, f);

	while (q--){
		cin >> c;
		if (c == 'Z'){
			cin >> v;
			cout << query(v) << "\n";
		}
		else{
			cin >> id >> x;
			update(id, x);
		}
	}

	return 0;
}
