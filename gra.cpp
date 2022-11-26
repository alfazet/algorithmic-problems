//XVII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

void solve(){
    int n;
    cin >> n;
    vector <int> a(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    vector <int> dp(n + 1);
    dp[1] = a[1];
    for (int i = 1; i <= n; i++){
        dp[i] = max(dp[i - 1], a[i] - dp[i - 1]);
    }
    cout << dp[n] << "\n";
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
