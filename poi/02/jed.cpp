#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

void solve(){
    int n;
    cin >> n;
    if (n == 1){
        cout << "1\n";
        return;
    }
    vector <string> ans(n);
    ans[1] = "1";
    queue <int> q;
    q.push(1);

    while (!q.empty()){
        int r = q.front();
        q.pop();
        if (r == 0){
            cout << ans[r] << "\n";
            return;
        }
        for (int d = 0; d <= 1; d++){
            int new_r = (r * 10 + d) % n;
            if (ans[new_r].empty()){
                q.push(new_r);
                ans[new_r] = ans[r] + (char) ('0' + d);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    cin >> t;
    while (t--){
        solve();
    }
    return 0;
}   
