#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

vector <int> get_kmp(const string &s){
	int n = s.size();
	vector <int> p(n);
	for (int i = 1; i < n; i++){
		int k = p[i - 1];
		while (k > 0 && s[i] != s[k]){
			k = p[k - 1];
		}
		p[i] = k;
		if (s[i] == s[p[i]]){
			p[i]++;
		}
	}
	return p;
}

bool check(const string &s, const string &t){ // czy t moze byc szablonem
	vector <int> p = get_kmp(t + "$" + s);
	int n = s.size(), m = t.size(), last_pos = m + 1;
	for (int i = m + 1; i < m + 1 + n; i++){
		if (p[i] == m){
			if (i - m + 1 - (last_pos + m - 1) > 1){
				return false;
			}
			last_pos = i - m + 1;
		}
	}
	return true;
}

void solve(){
	string s;
    cin >> s;
	vector <int> p = get_kmp(s);
	vector <string> prefsufs;
	int cur_l = s.size();
	while (cur_l > 0){
		prefsufs.push_back(s.substr(0, cur_l));
		cur_l = p[cur_l - 1];
	}
	reverse(prefsufs.begin(), prefsufs.end());
	int prev_sz = 0, m;
	for (string t : prefsufs){
		m = t.size();
		if (m >= 2 * prev_sz){
			if (check(s, t)){
				cout << m << "\n";
				return;
			}
			else{
				prev_sz = m;
			}
		}
	}
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
