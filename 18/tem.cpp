#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;	

const int MAXN = 1e6 + 3, BASE = (1 << 20), INF = 1e9 + 3;

int st[2 * BASE + 3];

int query(int l, int r){
	l += BASE;
	r += BASE;
	int ans = max(st[l], st[r]);
	while (l / 2 != r / 2){
		if (l % 2 == 0){
			ans = max(ans, st[l + 1]);
		}
		if (r % 2 == 1){
			ans = max(ans, st[r - 1]);
		}
		l /= 2;
		r /= 2;
	}
	return ans;
}

void update(int i, int val){
	i += BASE;
	st[i] = val;
	while (i > 1){
		i /= 2;
		st[i] = max(st[2 * i], st[2 * i + 1]);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

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

	return 0;
}   
