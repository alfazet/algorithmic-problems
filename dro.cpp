// XXVIII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;	

#define ff first
#define ss second

const int MAXN = 1e4 + 3, MAXK = 103, MAXS = 2.5e4 + 3;
const lli INF = 9e18 + 3;

// dp[v][k] - najkrtosza minuta dotarcia do v jadąc k autobusami
lli dp[MAXN][MAXK], steps[MAXS]; // co ile minut jest dana linia
vector <pair <int, lli>> lines[MAXS]; 
// lines[x][i] = {v, t} = i-ty przystanek linii x to v oraz jest ona tam w minucie t (po raz pierwszy)
unordered_map <int, int> edges[MAXN];

lli cdiv(lli a, lli b){
	return (a + b - 1) / b;
}

lli next_bus_time(int l, int i, lli t){ // minuta odjazdu kolejnego autobusu linii l z jej i-tego przystanku, jeżeli teraz jest minuta t
	if (t <= lines[l][i].ss){
		return lines[l][i].ss;
	}
	return lines[l][i].ss + steps[l] * cdiv(t - lines[l][i].ss, steps[l]);
}

void solve(){
	int n, m, s, used_buses, a, b, l, v, v_0;
	lli t_0, w, first, so_far;
	cin >> n >> m >> s >> used_buses >> t_0;
	used_buses++;
	for (int i = 0; i < m; i++){
		cin >> a >> b >> w;
		edges[a][b] = w;
		edges[b][a] = w;
	}
	for (int i = 0; i < s; i++){
		cin >> l >> first >> steps[i];
		cin >> v_0;
		lines[i].emplace_back(v_0, first);
		so_far = first;
		for (int j = 1; j < l; j++){
			cin >> v;
			so_far += edges[v_0][v];
			lines[i].emplace_back(v, so_far);
			v_0 = v;
		}
	}
	
	for (int i = 1; i <= n; i++){
		for (int j = 0; j <= used_buses; j++){
			dp[i][j] = INF;
		}
	}
	dp[1][0] = t_0;
	lli prev_val, new_val;
	for (int k = 1; k <= used_buses; k++){
		for (int i = 0; i < s; i++){
			prev_val = INF;
			for (int j = 1; j < (int) lines[i].size(); j++){
				new_val = min(prev_val, next_bus_time(i, j - 1, dp[lines[i][j - 1].ff][k - 1])) + (lines[i][j].ss - lines[i][j - 1].ss);
				dp[lines[i][j].ff][k] = min(dp[lines[i][j].ff][k], new_val);
				prev_val = new_val;
			}
		}
	}
	
	lli ans = INF;
	for (int i = 0; i <= used_buses; i++){
		ans = min(ans, dp[n][i]);
	}
	if (ans == INF) cout << "NIE\n";
	else cout << ans << "\n";
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
