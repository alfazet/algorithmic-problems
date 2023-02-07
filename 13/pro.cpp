#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e6 + 3, INF = 1e9 + 3;

vector <int> adj[MAXN];
int out_deg[MAXN], dp[MAXN];
bool reachable[MAXN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int n, m, a, b;
	cin >> n >> m;
	dp[n + 1] = 1;
	for (int i = 0; i < m; i++){
		cin >> a >> b;
		adj[b].push_back(a);
		out_deg[a]++;
	}

	queue <int> q;
	q.push(n + 1);
	while (!q.empty()){
		int v = q.front();
		q.pop();
		reachable[v] = true;
		for (int child : adj[v]){
			if (!reachable[child]){
				q.push(child);
			}
		}
	}

	while (!q.empty()) q.pop();
	for (int i = 1; i <= n + 1; i++){
		if (out_deg[i] == 0) q.push(i);
	}
	while (!q.empty()){
		int v = q.front();
		q.pop();
		for (int child : adj[v]){
			if (dp[child] < 36'500){
				dp[child] += dp[v];
				if (dp[child] > 36'500){
					dp[child] = INF;
				}
			}
			out_deg[child]--;
			if (out_deg[child] == 0){
				q.push(child);
			}
		}
	}

	for (int i = 1; i <= n; i++){
		if (out_deg[i] != 0 && reachable[i]){
			dp[i] = INF;
		}
	}

	int mx = 0;
	for (int i = 1; i <= n; i++){
		if (reachable[i]){
			mx = max(mx, dp[i]);
		}
	}

	if (mx == INF){
		cout << "zawsze\n";
	}
	else{
		cout << mx << "\n";
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++){
		cnt += (dp[i] == mx);
	}
	cout << cnt << "\n";
	for (int i = 1; i <= n; i++){
		if (dp[i] == mx){
			cout << i << " ";
		}
	}
	cout << "\n";

    return 0;
}   
