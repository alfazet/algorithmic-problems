//XX OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

void solve(){
    int n, m, x, len = 0;
    cin >> n >> m;
    vector <int> ile(m + 1), a(n + 1), req(n + 1);
    for (int i = 0; i < m; i++){
        cin >> ile[i];
        len += ile[i];
    }
    for (int i = 0; i < m; i++){
        cin >> x;
        x--;
        req[x] = ile[i];
    }
    for (int i = 0; i < n; i++){
        cin >> a[i];
        a[i]--;
    }

    if (len > n){
        cout << "0\n";
        return;
    }

    vector <int> cur_cnt(n + 1);
    int zgod = 0, ans = 0;
    for (int i = 0; i < n; i++){
        if (i >= len){
            if (cur_cnt[a[i - len]] == req[a[i - len]]){
                zgod--;
            }
            cur_cnt[a[i - len]]--;
            if (cur_cnt[a[i - len]] == req[a[i - len]]){
                zgod++;
            }
        }
        if (cur_cnt[a[i]] == req[a[i]]){
            zgod--;
        }
        cur_cnt[a[i]]++;
        if (cur_cnt[a[i]] == req[a[i]]){
            zgod++;
        }
        if (zgod == m){
            ans++;
        }
    }
    cout << ans << "\n";
}

int main (){
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
