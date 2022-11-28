#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 253;

vector <int> adj[MAXN];
bool vis[MAXN][MAXN][2]; // state (u, v), 0/1 - first / second agent about to move

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m, a, b, sa, sb, moves = 0;
	cin >> n >> m >> sa >> sb;
	for (int i = 0; i < m; i++){
		cin >> a >> b;
		adj[a].push_back(b);
	}

	queue <pair <int, int>> q1, q2; // first / second agent about to move
	q1.emplace(sa, sb);
	vis[sa][sb][0] = true;
	while (!q1.empty()){
		while (!q1.empty()){
			auto [u, v] = q1.front();
			q1.pop();
			
			if (u == v){
				cout << moves << "\n";
				return 0;
			}
			
			for (int child : adj[u]){
				if (!vis[child][v][1]){
					vis[child][v][1] = true;
					q2.emplace(child, v);
				}
			}	
		}
		while (!q2.empty()){
			auto [u, v] = q2.front();
			q2.pop();
					   
			for (int child : adj[v]){
				if (!vis[u][child][0]){
					vis[u][child][0] = true;
					q1.emplace(u, child);
				}
			}
		}
		moves++;
	}
	cout << "NIE\n";

	return 0;
}
