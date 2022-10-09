//XXII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 2'000'003, BASE = (1 << 21);

int n, d;
lli a[MAXN], covered[MAXN], st[2 * BASE + 3], p;

lli query(int l, int r){
	l += BASE;
	r += BASE;
	lli ans = max(st[l], st[r]);
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

void solve(){
	cin >> n >> p >> d;
	for (int i = 0; i < n; i++){
		cin >> a[i];
	}
	
	for (int i = 0; i < d; i++){
		covered[0] += a[i];
	}
	for (int i = 1; i < n - d + 1; i++){
		covered[i] = covered[i - 1] - a[i - 1] + a[i + d - 1];
	}
	for (int i = 0; i < n - d + 1; i++){
		st[BASE + i] = covered[i];
	}
	for (int i = BASE - 1; i >= 1; i--){
		st[i] = max(st[2 * i], st[2 * i + 1]);
	}
	
	int ans = d;
	lli used = 0, temp;
	for (int j = 0; j < d; j++){
		used += a[j];
	}
	
	int i = 0;
	for (int j = d; j < n; j++){
		used += a[j];
		temp = query(i, j - d + 1);
		used -= temp;
		while (i < j - d + 1 && used > p){
			used += temp;
			used -= a[i];
			i++;
			temp = query(i, j - d + 1);
			used -= temp;
		}
		ans = max(ans, j - i + 1);
		used += temp;
	}
	cout << ans << "\n";
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
