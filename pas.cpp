//VII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1003;

int dp[MAXN], r, g, b;
bool seen[MAXN];

void precomp(){
	for (int i = 1; i < MAXN; i++){
		memset(seen, false, sizeof(seen));
		int mex = 0, v;
		for (int j = 0; j <= i - r; j++){ // kladziemy czerwony
			v = dp[j] ^ dp[i - j - r];
			seen[v] = true;
			while (seen[mex]){
				mex++;
			}
		}
		for (int j = 0; j <= i - g; j++){ // kladziemy zielony
			v = dp[j] ^ dp[i - j - g];
			seen[v] = true;
			while (seen[mex]){
				mex++;
			}
		}
		for (int j = 0; j <= i - b; j++){ // kladziemy niebieski
			v = dp[j] ^ dp[i - j - b];	
			seen[v] = true;
			while (seen[mex]){
				mex++;
			}
		}
		dp[i] = mex;
	}
}

void solve(){
	int Q, k;
	cin >> r >> g >> b;
	precomp();
	cin >> Q;
	while (Q--){
		cin >> k;
		cout << (dp[k] > 0 ? "1\n" : "2\n");
	}
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
