#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MOD = 1e9 + 7;

lli madd(lli a, lli b){
    return (a + b) % MOD;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	string s;
	cin >> s;
	int n = s.size();
	
	for (char c : s){
		if (c == 'm' || c == 'w'){
			cout << "0\n";
			return 0;
		}
	}
	
	vector <lli> dp(n + 1); // dp[i] - cout of possible strings of length i
	dp[0] = dp[1] = 1;
	for (int i = 1; i < n; i++){
		dp[i + 1] = dp[i];
		if (s[i] == s[i - 1] && (s[i] == 'n' || s[i] == 'u')){
			dp[i + 1] = madd(dp[i + 1], dp[i - 1]);
		}
	}
	cout << dp[n] << "\n";

    return 0;
}   
