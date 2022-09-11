//XVIII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int n, k, lit;
const int MAXN = 3e5 + 3, INF = 1e9 + 3;

vector <int> adj[MAXN];
bool marked[MAXN];
vector <int> dp, nearest_lit;

void DFS(int v, int par, const int &t){
	bool skip = false;
	if (adj[v].size() == 1 && par != -1){
		dp[v] = (marked[v] ? 0 : -INF);
		nearest_lit[v] = INF;
		skip = true;
	}
	for (int child : adj[v]){
		if (child != par){
			DFS(child, v, t);
			dp[v] = max(dp[v], dp[child]);
			nearest_lit[v] = min(nearest_lit[v], nearest_lit[child]);
		}
	}
	if (!skip){
		dp[v]++;
		nearest_lit[v]++;
	}
	if (marked[v] && nearest_lit[v] > t){
		dp[v] = max(dp[v], 0);
	}
	if (dp[v] + nearest_lit[v] <= t){
		dp[v] = -INF;
	}
	if (dp[v] >= t){
		lit++;
		nearest_lit[v] = 0;
		dp[v] = -INF;
	}
}

bool check(int t){ //czy da sie dla danego czasu
	dp.assign(n + 1, -INF);
	nearest_lit.assign(n + 1, INF);
	lit = 0;
	DFS(1, -1, t);
	if (dp[1] > 0){
		lit++;
	}
	return lit <= k;
}

void solve(){
	int a, b;
	cin >> n >> k;
	for (int i = 1; i <= n; i++){
		cin >> marked[i];
	}
	for (int i = 0; i < n - 1; i++){
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	int l = 0, r = n, mid, ans = n;
	while (l <= r){
		mid = (l + r) / 2;
		if (check(mid)){
			ans = min(ans, mid);
			r = mid - 1;
		}
		else{
			l = mid + 1;
		}
	}
	cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    t = 1;
    //cin >> t;
    while (t--){
        solve();
    }
    return 0;
}   
