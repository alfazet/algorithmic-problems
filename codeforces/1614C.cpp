#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MOD = 1e9 + 7;

lli mmul(lli a, lli b){
	return (a * b) % MOD;
}

// turns out that sum of XORs over all subsets = OR of entire array * 2^(n-1)
void solve(){
	int n, m, l, r, x, all_or = 0;
	cin >> n >> m;
	for (int i = 0; i < m; i++){
		cin >> l >> r >> x;
		all_or |= x; // since OR is idempotent
	}
	
	lli p = 1;
	for (int i = 0; i < n - 1; i++){
		p = mmul(p, 2);
	}
	cout << mmul(p, all_or) << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
