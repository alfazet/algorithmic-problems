//XIV OI
#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

const int MAXN = 300003, BASE = (1 << 19);

vector <int> adj[MAXN];
int timer;
int depth[MAXN], in[MAXN], out[MAXN], st[2 * BASE];

void DFS(int v, int par, int dep){
	in[v] = timer++;
	depth[v] = dep;
	for (int child : adj[v]){
		if (child != par){
			DFS(child, v, dep + 1);	
		}
	}
	out[v] = timer++;
}

int query(int qi){
	int ans = 0, si = BASE + qi;
	ans += st[si];
	while (si > 1){
		si /= 2;
		ans += st[si];
	}
	return ans;
}

void update(int us, int ue, int val){
	int si_l = BASE + us, si_r = BASE + ue;
	st[si_l] += val;
	if (si_l != si_r){
		st[si_r] += val;
	}
	while (si_l / 2 != si_r / 2){
		if (si_l % 2 == 0){
			st[si_l + 1] += val;
		}
		if (si_r % 2 == 1){
			st[si_r - 1] += val;	
		}
		si_l /= 2;
		si_r /= 2;
	}
}

void solve(){
	int n, a, b, v, q;
	cin >> n;
	for (int i = 0; i < n - 1; i++){
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	DFS(1, -1, 0);
	char c;
	cin >> q;
	for (int i = 0; i < n + q - 1; i++){
		cin >> c;
		if (c == 'W'){
			cin >> v;
			cout << depth[v] - query(in[v]) << "\n";
		}
		else{
			cin >> a >> b;
			update(in[b], out[b], 1);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	int t;
	t = 1;
	//cin >> t;
	while (t--){
		solve();
	}
	return 0;
}
