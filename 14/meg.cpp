#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

const int MAXN = 2.5e5 + 3, BASE = (1 << 19);

vector <int> adj[MAXN];
int depth[MAXN], pre[MAXN], post[MAXN], st[2 * BASE + 3], timer;

void DFS(int v, int par, int dep){
	pre[v] = timer++;
	depth[v] = dep;
	for (int child : adj[v]){
		if (child != par){
			DFS(child, v, dep + 1);	
		}
	}
	post[v] = timer++;
}

int query(int i){
	i += BASE;
	int ans = st[i];
	while (i > 1){
		i /= 2;
		ans += st[i];
	}
	return ans;
}

void update(int l, int r, int val){
	l += BASE;
	r += BASE;
	st[l] += val;
	if (l != r){
		st[r] += val;
	}
	while (l / 2 != r / 2){
		if (l % 2 == 0){
			st[l + 1] += val;
		}
		if (r % 2 == 1){
			st[r - 1] += val;	
		}
		l /= 2;
		r /= 2;
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

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
			cout << depth[v] - query(pre[v]) << "\n";
		}
		else{
			cin >> a >> b;
			update(pre[b], post[b], 1);
		}
	}

	return 0;
}
