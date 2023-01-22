#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

// Erdos-Szekeres theorem: in a sequence of n elements there's either a non-decreasing or non-increasing subseqence of length >= sqrt(n)

void solve(){
    int n;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    auto check = [&](int l, int r){
        int mx, mn;
        for (int i = l; i <= r; i++){
            for (int j = i + 1; j <= r; j++){
                for (int k = j + 1; k <= r; k++){
                    mn = min(a[i], a[k]);
                    mx = max(a[i], a[k]);
                    if (mn <= a[j] && a[j] <= mx){
                        return false;
                    }
                }
            }
        }
        return true;
    };

    int ans = 0;
    for (int i = 0; i < n; i++){
        for (int j = i; j < min(n, i + 4); j++){ // since sqrt(5) > 2, every window of size >= 5 will contain a "bad triple"
            ans += check(i, j);
        }
    }
    cout << ans << "\n";
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
