#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const int MAXN = 2e6 + 3;

char s[MAXN];
pair <int, int> dp[MAXN];

void rec(int l, int r, int sum){
	if (sum <= 0){
		return;
	}
	dp[sum] = {l, r};
	if (s[l] == 'T'){
		rec(l + 1, r, sum - 2);
	}
	else if (s[r] == 'T'){
		rec(l, r - 1, sum - 2);
	}
	else{
		rec(l + 1, r - 1, sum - 2);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    
	int n, q, val, sum = 0;
	cin >> n >> q;
	int first_one = n + 1, last_one = -1;
	
	for (int i = 1; i <= n; i++){
		cin >> s[i];
		sum += (s[i] == 'W' ? 1 : 2);
		if (s[i] == 'W'){
			first_one = min(first_one, i);
			last_one = max(last_one, i);
		}
		
	}
	rec(1, n, sum);
	if (first_one < n){
		rec(first_one + 1, n, sum - 1 - 2 * (first_one - 1));
	}
	if (last_one > 1){
		rec(1, last_one - 1, sum - 1 - 2 * (n - last_one));
	}
	
	while (q--){
		cin >> val;
		if (dp[val].ff == 0){
			cout << "NIE\n";
		}
		else{
			cout << dp[val].ff << " " << dp[val].ss << "\n";
		}
	}
	
	return 0;
}
