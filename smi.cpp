//XVIII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e5 + 3;

int deg[MAXN], cur_cycle_start;
vector <int> adj[MAXN], where_opposite[MAXN]; // where_opposite[u][i] - jaki indeks ma krawędź u-adj[u][i] w liście adj[v]
bool on_stack[MAXN];
stack <int> cur_stack;
vector <vector <int>> cycles;

void add_edge(int u, int v){
	deg[u]++;
	deg[v]++;
	adj[u].push_back(v);
	adj[v].push_back(u);
	where_opposite[u].push_back(adj[v].size() - 1);
	where_opposite[v].push_back(adj[u].size() - 1);
}

void mark_as_used(int v){
	assert(adj[v].back() != -1);
	adj[adj[v].back()][where_opposite[v][adj[v].size() - 1]] = -1;
	adj[v].back() = -1;
}

void DFS(int v){
	on_stack[v] = true;
	cur_stack.push(v);
	while(!adj[v].empty()){
		int child = adj[v].back();
		if (child == -1){
			adj[v].pop_back();
			continue;
		}
		mark_as_used(v);
		adj[v].pop_back();
		if (on_stack[child]){
			cur_cycle_start = child;
			cycles.push_back({v});
			break;
		}
		else{
			DFS(child);
			cycles.back().push_back(v);
			if (v == cur_cycle_start){
				cur_cycle_start = -1;
			}
			else{
				break;
			}
		}
	}
	on_stack[v] = false;
	cur_stack.pop();
}

void solve(){
    int n, m, s1, s2, a, b;
	cin >> n >> m;
	for (int i = 0; i < m; i++){
		cin >> a >> b >> s1 >> s2;
		if (s1 != s2){
			add_edge(a, b);
		}
	}
	for (int i = 1; i <= n; i++){
		if (deg[i] % 2 == 1){
			cout << "NIE\n";
			return;
		}
	}
	for (int i = 1; i <= n; i++){
		DFS(i);
	}
	cout << cycles.size() << "\n";
	for (vector <int> v : cycles){
		cout << v.size() << " ";
		for (int x : v){
			cout << x << " ";
		}
		cout << v[0] << "\n";
	}
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
