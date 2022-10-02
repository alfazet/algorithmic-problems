//XXIII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MOD = 1e9 + 7, MAXN = 1e6 + 3, BASE = (1 << 21);

lli swaps_to_prev[MAXN], swaps_to_sort[MAXN];

int st[2 * BASE + 3];

int query(int qs, int qe){
	int si_l = BASE + qs, si_r = BASE + qe, ans = st[si_l];
	if (si_l != si_r){
		ans += st[si_r];
	}
	while (si_l / 2 != si_r / 2){
		if (si_l % 2 == 0){
			ans += st[si_l + 1];
		}
		if (si_r % 2 == 1){
			ans += st[si_r - 1];
		}
		si_l /= 2;
		si_r /= 2;
	}
	return ans;
}

void update(int ui){
	int si = BASE + ui;
	st[si]++;
	while (si > 1){
		si /= 2;
		st[si] = st[2 * si] + st[2 * si + 1];
	}
}

lli madd(lli a, lli b){
	return (a + b) % MOD;
}

lli mmul(lli a, lli b){
	return (a * b) % MOD;
}

void solve(){
	int n;
	cin >> n;
	vector <int> p(n);
	for (int i = 0; i < n; i++){
		cin >> p[i];
	}
	
	for (int i = 1; i <= n; i++){
		swaps_to_prev[i] = (i + 1) / 2;
		swaps_to_sort[i] = madd(swaps_to_sort[i], madd(mmul(i - 1, swaps_to_prev[i]), mmul(i, swaps_to_sort[i - 1])));
	}
	
	lli ans = 0;
	for (int i = n - 1; i >= 0; i--){
		int l = n - 1 - i + 1;
		ans = madd(ans, mmul(query(1, p[i] - 1), madd(swaps_to_prev[l], swaps_to_sort[l - 1])));
		update(p[i]);
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
