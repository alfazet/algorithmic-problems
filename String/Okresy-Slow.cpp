//XIII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

void solve(){
	int n;
	string s;
	cin >> n >> s;
	vector <int> p(n), min_p(n);
	min_p[0] = 1;
	for (int i = 1; i < n; i++){
		int k = p[i - 1];
		while (k > 0 && s[k] != s[i]){
			k = p[k - 1];
		}
		p[i] = k;
		if (s[i] == s[p[i]]){
			p[i]++;
		}
		min_p[i] = (p[i] == 0 ? i + 1 : p[i]);
	}
	for (int i = 1; i < n; i++){
		min_p[i] = min(min_p[i], min_p[min_p[i] - 1]);
	}
	lli ans = 0;
	for (int i = 1; i < n; i++){
		ans += (i + 1) - min_p[i];
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
