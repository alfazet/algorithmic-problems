#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MOD = 1e9 + 7;

struct BIT{
	int n;
	vector <int> bit;

	void init(int n_){
		n = n_;
		bit.resize(n + 1);
	}

	int query(int i){
		int ans = 0;
		while (i >= 1){
			ans += bit[i];
			i -= (i & -i);
		}
		return ans;
	}

	int query(int l, int r){
		return query(r) - (l == 1 ? 0 : query(l - 1));
	}

	void update(int i, int val){
		while (i <= n){
			bit[i] += val;
			i += (i & -i);
		}
	}
};

lli madd(lli a, lli b){
	return (a + b) % MOD;
}

lli mmul(lli a, lli b){
	return (a * b) % MOD;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int n;
	cin >> n;

	vector <lli> moves_to_prev(n + 1); // (n, 1, 2, ..., n - 1) -> (n - 1, n, n - 2, ..., 1)
	for (int i = 1; i <= n; i++){
		moves_to_prev[i] = (i - 1) / 2 + 1;
	}
	vector <lli> moves_to_reverse(n + 1); // (n, n - 1, n - 2, ..., 1) -> (1, 2, 3, ..., n)
	moves_to_reverse[2] = 1;
	for (int i = 3; i <= n; i++){
		moves_to_reverse[i] = madd(mmul(moves_to_reverse[i - 1], i), mmul(moves_to_prev[i], i - 1));
	}

	vector <int> a(n + 1);
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	BIT bit;
	bit.init(n);

	lli ans = 0;
	for (int i = n; i >= 1; i--){
		int cnt_smaller = bit.query(1, a[i] - 1);
		ans = madd(ans, mmul(cnt_smaller, madd(moves_to_prev[n - i + 1], moves_to_reverse[n - i]))); // move from (..., x, sorted) to (..., sorted with x)
		bit.update(a[i], 1);
	}
	cout << ans << "\n";

    return 0;
}   
