#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

vector <lli> f;

void solve(){
    lli n;
    cin >> n;

    auto first_larger = [&](int &i){
        while (f[i - 1] > n){
            i--;
        }
    };

    int ans = 0, i = f.size() - 1;
    first_larger(i);
    while (n > 0){
        if (n - f[i - 1] <= f[i] - n){
            n = n - f[i - 1];
        }
        else{
            n = f[i] - n;
        }
        ans++;
        first_larger(i);
    }
    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    f.push_back(0);
    f.push_back(1);
    while (f.back() <= (lli) 1e18){
        f.push_back(f.end()[-1] + f.end()[-2]);
    }

    int t = 1;
    cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
