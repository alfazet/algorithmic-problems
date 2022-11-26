//XXIV OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int SQRT = 317;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, q, start, steps, d;
	cin >> n >> q;
	vector <int> ans(n), add(n), sub(n);
	vector <vector <pair <int, int>>> big_queries(n, vector <pair <int, int>>());
	while (q--){
		cin >> start >> steps >> d;
		start--;
		if (d >= SQRT){
			for (int i = 0; i < steps; i++){
				ans[start + i * d]++;
			}
		}
		else{
			big_queries[d].emplace_back(start, steps);
		}
	}
	for (int d = 1; d < min(n, SQRT); d++){
		for (auto [start, steps] : big_queries[d]){
			add[start]++;
			sub[start + (steps - 1) * d]++;
		}
		for (int i = 0; i < n; i++){
			ans[i] += add[i];
			add[i] -= sub[i];
			if (i + d < n){
				add[i + d] += add[i];
			}
			add[i] = 0;
			sub[i] = 0;
		}
	}

	for (int x : ans){
		cout << x << " ";
	}
	cout << "\n";

	return 0;
}
