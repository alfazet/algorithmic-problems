#include <bits/stdc++.h>
typedef long long int lli;
using namespace std; 

const int MAXN = 2e5 + 3;

vector <int> adj[MAXN];
bool vis[MAXN];
int color[MAXN];

void DFS(int v, int c){
	vis[v] = true;
	if (color[v] == 0){
		color[v] = c;	
	}
	
	for (int child : adj[v]){
		if (!vis[child]){
			DFS(child, (c == 1 ? 2 : 1));
		}
	}
}

int main (){
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
		if (adj[i].empty()){
			cout << "NIE\n";
			return 0;
		}
		if (!vis[i]){
			DFS(i, 1);
		}
	}
	cout << "TAK\n";
	for (int i = 1; i <= n; i++){
		cout << (color[i] == 1 ? "K\n" : "S\n");
	}

    return 0;
}
