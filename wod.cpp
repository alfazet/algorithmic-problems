//VI OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const int MAXN = 103, INF = 1e4 + 3, dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int n, m, h_start[MAXN][MAXN], h_wody[MAXN][MAXN];

bool valid(int r, int c){
	return r >= 0 && r <= n - 1 && c >= 0 && c <= m - 1;
}

bool border(int r, int c){
	return r == 0 || r == n - 1 || c == 0 || c == m - 1;
}

void DFS(int r, int c, int h){
	if (border(r, c)){
		h_wody[r][c] = h_start[r][c];
	}
	else{
		h_wody[r][c] = h;	
	}
	int new_r, new_c;
	for (int i = 0; i < 4; i++){
		new_r = r + dx[i];
		new_c = c + dy[i];
		if (valid(new_r, new_c) && !h_wody[new_r][new_c] && h_start[new_r][new_c] <= h){
			DFS(new_r, new_c, h);
		}
	}
}

void solve(){
	cin >> n >> m;
	vector <pair <int, pair <int, int>>> kolejnosc;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			cin >> h_start[i][j];
			kolejnosc.push_back({h_start[i][j], {i, j}});
		}
	}
	sort(kolejnosc.begin(), kolejnosc.end());
	int r, c, new_r, new_c;
	bool ok;
	for (auto p : kolejnosc){
		r = p.ss.ff;
		c = p.ss.ss;
		ok = false;
		if (border(r, c)){
			ok = true;
		}
		else{
			for (int i = 0; i < 4; i++){
				new_r = r + dx[i];
				new_c = c + dy[i];
				if (h_wody[new_r][new_c]){
					ok = true;
				}
			}			
		}
		if (ok){
			DFS(r, c, h_start[r][c]);
		}
	}
	
	int ans = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			ans += h_wody[i][j] - h_start[i][j];
		}
	}
	cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    //cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
