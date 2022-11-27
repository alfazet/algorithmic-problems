#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int BASE = (1 << 20);

lli st[2 * BASE + 3];

lli query(int l, int r){
	l += BASE;
	r += BASE;
	lli ans = st[l];
	if (l != r){
		ans += st[r];
	}
	while (l / 2 != r / 2){
		if (l % 2 == 0){
			ans += st[l + 1];
		}
		if (r % 2 == 1){
			ans += st[r - 1];
		}
		l /= 2;
		r /= 2;
	}
	return ans;
}

void update(int i){
	i += BASE;
	st[i]++;
	while (i > 1){
		i /= 2;
		st[i] = st[2 * i] + st[2 * i + 1];
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;
	string s, t;
	cin >> s >> t;
	vector <queue <int>> positions(26);
	for (int i = 0; i < n; i++){
		positions[s[i] - 'A'].push(i);
	}

	lli ans = 0;
	for (int i = 0; i < n; i++){
		int closest = positions[t[i] - 'A'].front();
		positions[t[i] - 'A'].pop();
		ans += closest - i + query(closest + 1, n); // roznica pozycji + o ile przesunęła się litera
		update(closest);
	}
	cout << ans << "\n";

	return 0;
}
