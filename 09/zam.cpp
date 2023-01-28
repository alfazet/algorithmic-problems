#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1003;

int c[MAXN];
bool vis[MAXN][MAXN];
vector <int> adj[MAXN]; // {v, money}
pair <int, int> prv[MAXN][MAXN];

void DFS(int v, int m){
	vis[v][m] = true;
	for (int child : adj[v]){
		if (c[child] <= m && !vis[child][m - c[child]]){
			prv[child][m - c[child]] = {v, m};
			DFS(child, m - c[child]);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m, a, b, start, end, s;
	cin >> n >> m >> start >> end >> s;
	for (int i = 1; i <= n; i++){
		cin >> c[i];
	}
	for (int i = 0; i < m; i++){
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	DFS(start, s - c[start]);
	
	prv[start][s - c[start]] = {-1, -1};
	int v = end, money = 0;
	vector <int> ans;
	while (prv[v][money] != pair{-1, -1}){
		ans.push_back(v);
		pair <int, int> temp = prv[v][money];
		v = temp.first;
		money = temp.second;
	}
	ans.push_back(start);
	reverse(ans.begin(), ans.end());
	for (int x : ans){
		cout << x << " ";
	}
	cout << "\n";
	
	return 0;
}
