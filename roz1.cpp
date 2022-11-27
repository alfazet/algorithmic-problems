//XIX OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

void solve(){
    lli n;
    cin >> n;
    int ans = 0;
    vector <lli> F;
    F.push_back(0);
    F.push_back(1);
    int i = 1;
    while (F[i] <= n){
        F.push_back(F[i] + F[i - 1]);
        i++;
    }
    while (n > 0){
        if (n - F[i - 1] <= F[i] - n){
            n -= F[i - 1];
        }
        else{
            n = F[i] - n;
        }
        ans++;
        while (F[i - 1] > n){
            i--;
        }
    }
    cout << ans << "\n";
}

int main (){
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
