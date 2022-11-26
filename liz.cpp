//IV OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

void solve(){
    int n, k;
    cin >> n >> k;
    int mx_suma = n * (n + 1) / 2;
    vector <vector <lli>> dp(n + 1, vector <lli>(mx_suma + 1));
    for (int i = 0; i <= n; i++){
        dp[i][i] = 1;
    }
    for (int i = 1; i <= n; i++){
        for (int j = i; j <= mx_suma; j++){
            for (int k = 1; k <= i - 2; k++){
                dp[i][j] += dp[k][j - i];
            }
        }
    }
    lli ans = 0;
    for (int i = 0; i <= n; i++){
        for (int j = k + 1; j <= mx_suma; j++){
            ans += dp[i][j];
        }
    }
    cout << ans << "\n";
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
