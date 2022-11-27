//II OI
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
    queue <int> q;
    q.push(1);
    ans[1] = "1";
    while (!q.empty()){
        int rem = q.front();
        q.pop();
        if (rem == 0){
            cout << ans[rem] << "\n";
            return;
        }
        int r1 = (10 * rem) % n;
        if (ans[r1].empty()){
            ans[r1] = ans[rem] + '0';
            q.push(r1);
        }
        int r2 = (10 * rem + 1) % n;
        if (ans[r2].empty()){
            ans[r2] = ans[rem] + '1';
            q.push(r2);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    //t = 1;
    cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
