#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e6 + 33;

int p[MAXN];

void fill_kmp(const string &s){
	int n = s.size();
	p[0] = 0;
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
}

bool check(const string &s, const string &t){ // czy t moze byc szablonem
	fill_kmp(t + "$" + s);
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
	fill_kmp(s);
	vector <int> prefsuf_sizes;
	int cur_l = s.size();
	while (cur_l > 0){
		prefsuf_sizes.push_back(cur_l);
		cur_l = p[cur_l - 1];
	}
	reverse(prefsuf_sizes.begin(), prefsuf_sizes.end());
	int prev_sz = 0;
	for (int l : prefsuf_sizes){
		if (l >= 2 * prev_sz){
			if (check(s, s.substr(0, l))){
				cout << l << "\n";
				return;
			}
			else{
				prev_sz = l;
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
