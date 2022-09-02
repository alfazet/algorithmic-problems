#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;	

const int MAXN = 1e6 + 3, BASE = (1 << 20), INF = 1e9 + 3;

int st[2 * BASE + 3];

int query(int qs, int qe){
	int si_l = qs + BASE, si_r = qe + BASE, ans = max(st[si_l], st[si_r]);
	while (si_l / 2 != si_r / 2){
		if (si_l % 2 == 0){
			ans = max(ans, st[si_l + 1]);
		}
		if (si_r % 2 == 1){
			ans = max(ans, st[si_r - 1]);
		}
		si_l /= 2;
		si_r /= 2;
	}
	return ans;
}

void update(int ui, int val){
	int si = BASE + ui;
	st[si] = val;
	while (si > 1){
		si /= 2;
		st[si] = max(st[2 * si], st[2 * si + 1]);
	}
}

void solve(){
	int n;
	cin >> n;
	vector <int> l(n + 1), r(n + 1);
	for (int i = 1; i <= 2 * BASE + 2; i++){
		st[i] = -INF;
	}
	for (int i = 1; i <= n; i++){
		cin >> l[i] >> r[i];
		update(i, l[i]);
	}
	int p = 1, k = 1, best = 1;
	while (k < n){
		if (query(p, k) <= r[k + 1]){
			k++;
		}
		else{
			p++;
			k = max(k, p);
		}
		best = max(best, k - p + 1);
	}
	cout << best << "\n";
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
