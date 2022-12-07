#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;
 
const int MAXM = 2e5 + 3, MOD = 1e9 + 7;

lli madd(lli a, lli b){
	return (a + b) % MOD;
}

lli dp[MAXM][10][10]; // dp[i][x][d] - number of digits x after i moves, if there was only a single digit d at the start
 
void solve(){
	int n, m, d;
	cin >> n >> m;
	lli ans = 0;
	while (n){
		d = n % 10;
		n /= 10;
		for (int x = 0; x <= 9; x++){
			ans = madd(ans, dp[m][x][d]);
		}
	}
	cout << ans << "\n";
}
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for (int d = 0; d <= 9; d++){
		dp[0][d][d] = 1;
		for (int i = 1; i < MAXM; i++){
			for (int x = 2; x <= 9; x++){
				dp[i][x][d] = dp[i - 1][x - 1][d];
			}
			dp[i][1][d] = madd(dp[i - 1][0][d], dp[i - 1][9][d]);
			dp[i][0][d] = dp[i - 1][9][d];
		}
	}

	int t = 1;
	cin >> t;
	while (t--){
		solve();
	}
	return 0;
}
