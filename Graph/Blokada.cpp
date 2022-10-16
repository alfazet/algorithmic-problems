//XV OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e5 + 3;

lli ans[MAXN];
int low[MAXN], pre[MAXN], sub_sz[MAXN], timer = 1, n; // sub_sz[v] nie uwzglednia v
vector <int> adj[MAXN], cut_comps[MAXN];

void DFS(int v, int par){
	pre[v] = low[v] = timer++;
	sub_sz[v] = 1;
	for (int child : adj[v]){
		if (child != par){
			if (pre[child] == 0){
				DFS(child, v);
				sub_sz[v] += sub_sz[child];
				low[v] = min(low[v], low[child]);
				if (low[child] >= pre[v]){
					cut_comps[v].push_back(child);
				}
			}
			else{
				low[v] = min(low[v], pre[child]);
			}
		}
	}
	
	int rest = n - 1; // rest = wszystko powyżej v
	for (int child : cut_comps[v]){
		rest -= sub_sz[child];
	}
	for (int child : cut_comps[v]){
		ans[v] += 1LL * sub_sz[child] * (n - 1 - sub_sz[child]); // nie przejdziemy z poddrzewa do wszystkiego innego
		ans[v] += 1LL * sub_sz[child] * rest; // nie przejdziemy z poddrzewa do rest
	}
}

void solve(){
	int m, a, b;
	cin >> n >> m;
	for (int i = 0; i < m; i++){
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	DFS(1, -1);
	for (int i = 1; i <= n; i++){
		cout << ans[i] + 2 * (n - 1) << "\n";
	}
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    // cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
