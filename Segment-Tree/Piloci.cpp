#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

struct Node{
	int mn, mx;
};

const int MAXN = 3'000'007, INF = 2'000'000'007;

int a[MAXN];
Node st[2 * MAXN];

Node merge(Node l, Node r){
	return Node{min(l.mn, r.mn), max(l.mx, r.mx)};
}

void build(int n){
	for (int i = 0; i < n; i++){
		st[BASE + i] = Node{a[i], a[i]};
	}
	for (int i = BASE - 1; i >= 1; i--){
		st[i] = merge(st[2 * i], st[2 * i + 1]);
	}
}

Node query(int qs, int qe){
	int si_l = BASE + qs, si_r = BASE + qe;
	Node ans = st[si_l];
	if (si_l != si_r){
		ans = merge(ans, st[si_r]);
	}
	while (si_l / 2 != si_r / 2){
		if (si_l % 2 == 0){
			ans = merge(ans, st[si_l + 1]);
		}
		if (si_r % 2 == 1){
			ans = merge(ans, st[si_r - 1]);
		}
		si_l /= 2;
		si_r /= 2;
	}
	return ans;
}

void solve(){
    int n, t, ans = 1;
	cin >> t >> n;
	for (int i = 0; i < n; i++){
		cin >> a[i];
	}
	build(n);
	Node res;
	int i = 0, j = 0;
	while (j < n - 1){
		j++;
		res = query(i, j);
		while (i < j && res.mx - res.mn > t){
			i++;
			res = query(i, j);
		}
		ans = max(ans, j - i + 1);
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
