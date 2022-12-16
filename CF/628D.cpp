#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 2003, MOD = 1e9 + 7;

int M, D;
lli dp[MAXN][MAXN][2]; // dp[i][r][0/1] = number of prefixes of length i with remainder r mod m that are less than / equal to the corresponding prefix of x

lli madd(lli a, lli b){
	return (a + b) % MOD;
}

lli msub(lli a, lli b){
	return ((a - b) % MOD + MOD) % MOD;
}

bool is_magic(const vector <int> &x){
	int r = 0, n = x.size();
	for (int i = 0; i < n; i++){
		if ((i % 2 == 1 && x[i] != D) || (i % 2 == 0 && x[i] == D)){
			return false;
		}
		r *= 10;
		r += x[i];
		r %= M;
	}
	return r == 0;
}

bool ok(int d, int i){ // can digit d be in place i
	if (i % 2 == 1 && d != D) return false;
	if (i % 2 == 0 && d == D) return false;
	if (i == 0 && d == 0) return false;
	return true;
}

lli solve(const vector <int> &x){
	int n = x.size();
	for (int i = 0; i <= n; i++){
		for (int r = 0; r < M; r++){
			dp[i][r][0] = dp[i][r][1] = 0;
		}
	}
	dp[0][0][1] = 1;
	for (int i = 0; i < n; i++){
		for (int r = 0; r < M; r++){
			for (int d = 0; d <= 9; d++){ // previous one was smaller, so this one can be whatever
				if (ok(d, i)){
					dp[i + 1][(r * 10 + d) % M][0] = madd(dp[i + 1][(r * 10 + d) % M][0], dp[i][r][0]);
				}
			}
			
			for (int d = 0; d < x[i]; d++){ // previous one was equal, so this one has to be smaller
				if (ok(d, i)){
					dp[i + 1][(r * 10 + d) % M][0] = madd(dp[i + 1][(r * 10 + d) % M][0], dp[i][r][1]);
				}
			}
			
			if (ok(x[i], i)){ // previous one was equal and this one is equal as well
				dp[i + 1][(r * 10 + x[i]) % M][1] = madd(dp[i + 1][(r * 10 + x[i]) % M][1], dp[i][r][1]);
			}
		}
	}
	return madd(dp[n][0][0], dp[n][0][1]);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	cin >> M >> D;
	string temp_a, temp_b;
	cin >> temp_a >> temp_b;
	
	vector <int> a, b;
	for (char c : temp_a){
		a.push_back((int) (c - '0'));
	}
	for (char c : temp_b){
		b.push_back((int) (c - '0'));
	}

	cout << madd(msub(solve(b), solve(a)), (is_magic(a))) << "\n";
	
    return 0;
}   
