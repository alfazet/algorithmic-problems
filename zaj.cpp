//XXIII OI
#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

void solve(){
    int n, m, pos;
    cin >> n >> m;
    vector <vector <int>> dp(2, vector <int> (m + 1));
    vector <int> help(max(n, m) + 1);
    vector <int> a(n + 1), b(m + 1), prev_a(n + 1), prev_b(m + 1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++){
        cin >> b[i];
    }
    prev_a[0] = 0, prev_b[0] = 0;
    for (int i = 1; i <= n; i++){
        pos = 0;
        for (int j = i - 1; j >= 1; j--){
            if (a[j] == a[i]){
                pos = j;
                break;
            }
        }
        prev_a[i] = pos;
    }
    for (int i = 1; i <= m; i++){
        pos = 0;
        for (int j = i - 1; j >= 1; j--){
            if (b[j] == b[i]){
                pos = j;
                break;
            }
        }
        prev_b[i] = pos;
    }

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            if (a[i] == b[j] && prev_a[i] != 0 && prev_b[j] != 0){
                dp[i % 2][j] = help[prev_b[j]] + 2;
            }
            dp[i % 2][j] = max({dp[i % 2][j], dp[(i - 1) % 2][j], dp[i % 2][j - 1]});
        }
        for (int j = 1; j <= m; j++){
            if (a[i] == b[j]){
                help[j] = dp[(i - 1) % 2][j - 1];
            }
        }
    }
    cout << dp[n % 2][m] << "\n";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int t;
    t = 1;
    //cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
