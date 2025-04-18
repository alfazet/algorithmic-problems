#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

vector <int> get_kmp(string &s){
	int n = s.size();
	vector <int> p(n);
	for (int i = 1; i < n; i++){
		int k = p[i - 1];
		while (k > 0 && s[k] != s[i]){
			k = p[k - 1];
		}
		p[i] = k;
		if (s[p[i]] == s[i]){
			p[i]++;
		}
	}
	return p;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	string s;
	cin >> s;
	int n = s.size();

	auto check = [&](string t){ // check if s can be filled by occurences of t
		string comb = t + '#' + s;
		vector <int> p = get_kmp(comb);
		int m = t.size(), last_occ = 1;
		for (int i = m + 1; i < n + m + 1 - m + 1; i++){
			if (p[i + m - 1] == m){
				last_occ = i;
			}
			if (i - last_occ == m){
				return false;
			}
		}
		return true;
	};

	vector <int> p = get_kmp(s), prefsuf_lengths = {n};
	int i = n - 1;
	while (i > 0 && p[i] > 0){
		prefsuf_lengths.push_back(p[i]);
		i = p[i - 1];
	}
	reverse(prefsuf_lengths.begin(), prefsuf_lengths.end());

	int prev_len = 0;
	for (int l : prefsuf_lengths){
		if (l >= 2 * prev_len){
			if (check(s.substr(0, l))){
				cout << l << "\n";
				return 0;
			}
			prev_len = l;
		}
	}

	return 0;
}
