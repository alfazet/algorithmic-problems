#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1003, MAXL = 1e4 + 3;

vector <int> pos[MAXN][10]; // pos[i][d] - positions of digit d in i-th string, decreasingly
int ptrs[10];

bool check(int pin, int i){	
	int d, prev = MAXL;
	for (int j = 0; j <= 9; j++){
		ptrs[j] = 0;
	}
	for (int j = 0; j < 4; j++){
		d = pin % 10;
		pin /= 10;
		while (pos[i][d][ptrs[d]] > prev){
			ptrs[d]++;
		}
		if (pos[i][d][ptrs[d]] == -1){
			return false;
		}
		prev = pos[i][d][ptrs[d]];
	}
	return true;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	int n, l;
	cin >> n;
	string s;
	for (int i = 0; i < n; i++){
		cin >> l >> s;
		for (int j = l - 1; j >= 0; j--){
			pos[i][s[j] - '0'].push_back(j);
		}
		for (int d = 0; d <= 9; d++){
			pos[i][d].push_back(-1);
		}
	}
	
	int ans = 0;
	bool possible;
	for (int pin = 0; pin <= 9999; pin++){
		possible = true;
		for (int i = 0; i < n; i++){
			possible &= check(pin, i);
			if (!possible) break;
		}
		ans += possible;
	}
	cout << ans << "\n";
	
    return 0;
}
