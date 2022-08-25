#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1003;

vector <int> pos[MAXN][10];

string prepare(int pin){
	string s;
	if (pin < 1000){
		s += '0';
	}
	if (pin == 0){
		return s;
	}
	string p = to_string(pin);
	char last = '!';
	for (char c : p){
		if (c != last){
			s += c;
			last = c;
		}
	}
	return s;
}

bool check(string s, int id){
	int last_pos = -1, digit;
	for (char c : s){
		digit = (int) (c - '0');
		auto it = upper_bound(pos[id][digit].begin(), pos[id][digit].end(), last_pos);
		if (it == pos[id][digit].end()){
			return false;
		}
		last_pos = pos[id][digit][it - pos[id][digit].begin()];
	}
	return true;
}

void solve(){
	int n, l; 
	string s;
	cin >> n;
	for (int i = 0; i < n; i++){
		cin >> l >> s;
		for (int j = 0; j < l; j++){
			pos[i][(int) (s[j] - '0')].push_back(j);
		}
	}
	int ans = 0;
	bool ok;
	for (int pin = 0; pin <= 9999; pin++){
		ok = true;
		for (int i = 0; i < n; i++){
			if (!check(prepare(pin), i)){
				ok = false;
				break;
			}
		}
		ans += ok;
	}
	cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    t = 1;
    //cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
