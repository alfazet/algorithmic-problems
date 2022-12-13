#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m, k;
	cin >> n >> m >> k;
	vector <int> a(n), b(m), ans(n);
	vector <vector <int>> pos(k + 1);
	for (int i = 0; i < n; i++){
		cin >> a[i];
		pos[a[i]].push_back(i);
	}
	for (int i = 0; i < m; i++){
		cin >> b[i];
	}

	int ptr = 0;
	vector <int> start_pos(m);
	for (int i = 0; i < n; i++){
		if (a[i] == b[ptr]){
			start_pos[ptr] = i;
			ptr++;
		}
		if (ptr == m){
			break;
		}
	}

	int limit = n;
	vector <int> last_unchecked_occ(k + 1);
	for (int i = 1; i <= k; i++){
		last_unchecked_occ[i] = (int) pos[i].size() - 1;
	}

	for (int i = m - 1; i >= 0; i--){
		while (pos[b[i]].back() >= limit){
			pos[b[i]].pop_back();
		}
		limit = pos[b[i]].back();
		last_unchecked_occ[b[i]] = min(last_unchecked_occ[b[i]], (int) pos[b[i]].size() - 1);
		int j = last_unchecked_occ[b[i]];
		for (; j >= 0; j--){
			ans[pos[b[i]][j]] = true;
			if (pos[b[i]][j] == start_pos[i]){
				break;
			}
		}
		last_unchecked_occ[b[i]] = j - 1;
	}

	for (int x : ans){
		cout << x << " ";
	}
	cout << "\n";

	return 0;
}
