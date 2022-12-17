#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 3e5 + 3;

int tree[MAXN], dp[MAXN][23], k, ti = 1; // dp[v][i] = max. sum if we take i cards from subtree v

void DFS(int v){
	dp[v][1] = tree[v];
	if (2 * v < ti){
		DFS(2 * v);
		DFS(2 * v + 1);
		for (int j = 1; j <= k; j++){
			for (int i = 0; i <= j - 1; i++){
				dp[v][j] = max(dp[v][j], tree[v] + dp[2 * v][i] + dp[2 * v + 1][j - i - 1]);
			}
		}
	}
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	int n, x, y;
	cin >> n >> k;
	k /= 2;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < (1 << i); j++){
			cin >> x >> y;
			tree[ti] = x + y;
			ti++;
		}
	}
	DFS(1);
	int ans = 0;
	for (int j = 0; j <= k; j++){
		ans = max(ans, dp[1][j]);
	}
	cout << ans << "\n";

    return 0;
}   
