#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 5e5 + 3;

int scc[MAXN], in_deg[2][MAXN], id_in_topo[MAXN], scc_cnt;
vector <int> adj[2][2][MAXN], topo, post; // adj[0/1][0/1] - [normal / condensed][normal / trans]
bool vis[MAXN], good[2][MAXN];

void DFS1(int v){ // postorder
	vis[v] = true;
	for (int child : adj[0][0][v]){
		if (!vis[child]){
			DFS1(child);
		}
	}
	post.push_back(v);
}

void DFS2(int v){ // mark sccs
	scc[v] = scc_cnt;
	for (int child : adj[0][1][v]){
		if (scc[child] == 0){
			DFS2(child);
		}
	}
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	int n, m, a, b;
	cin >> n >> m;
	for (int i = 0; i < m; i++){
		cin >> a >> b;
		adj[0][0][a].push_back(b);
		adj[0][1][b].push_back(a);
	}

	for (int i = 1; i <= n; i++){
		if (!vis[i]){
			DFS1(i);
		}
	}
	reverse(post.begin(), post.end());
	for (int v : post){
		if (scc[v] == 0){
			scc_cnt++;
			DFS2(v);
		}
	}

	for (int r = 0; r <= 1; r++){
		for (int i = 1; i <= n; i++){
			for (int child : adj[0][r][i]){
				if (scc[i] != scc[child]){
					adj[1][r][scc[i]].push_back(scc[child]);
					in_deg[r][scc[child]]++;
				}
			}
		}
	}
	
	queue <int> q;
	for (int i = 1; i <= scc_cnt; i++){
		if (in_deg[0][i] == 0){
			q.push(i);
		}
	}
	while (!q.empty()){
		int v = q.front();
		q.pop();
		topo.push_back(v);
		for (int child : adj[1][0][v]){
			in_deg[0][child]--;
			if (in_deg[0][child] == 0){
				q.push(child);
			}
		}
	}

	for (int r = 0; r <= 1; r++){
		for (int i = 0; i < scc_cnt; i++){
			id_in_topo[topo[i]] = i;
		}

		int first_good = 0, min_from_here; // min_from_here - min id of a vertex we can reach from v

		for (int v : topo){
			if (id_in_topo[v] >= first_good){
				good[r][v] = true;
			}
			min_from_here = scc_cnt;
			for (int child : adj[1][r][v]){
				min_from_here = min(min_from_here, id_in_topo[child]);
			}
			first_good = max(first_good, min_from_here);
		}

		reverse(topo.begin(), topo.end()); // toposort of transposed graph == reverse toposort of normal graph
	}

	vector <int> ans;
	for (int i = 1; i <= n; i++){
		if (good[0][scc[i]] && good[1][scc[i]]){
			ans.push_back(i);
		}
	}
	cout << ans.size() << "\n";
	for (int v : ans){
		cout << v << " ";
	}
	cout << "\n";

    return 0;
}   
