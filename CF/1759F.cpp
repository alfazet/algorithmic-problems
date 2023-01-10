#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

void solve(){
	int n, p;
    cin >> n >> p;
    vector <int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int last_digit = a[n - 1];
    vector <int> old = a;

    auto check_before_change = [&](int k){
        int l = last_digit, r = k; // we've already seen everything from [l; r]
        set <int> vis;
        for (int i = 0; i < n - 1; i++){
            if (vis.count(a[i]) == 0 && (a[i] < l || a[i] > r)){
                vis.insert(a[i]);
            }
        }
        return (int) vis.size() + (r - l + 1) == p;
    };

    auto check_after_change = [&](int k){
        int l = 0, r = k;
        set <int> vis;
        for (int i = 0; i < n - 1; i++){
            if (a[i] > r && a[i] < last_digit){
                vis.insert(a[i]);
            }
        }
        for (int i = 0; i < n - 1; i++){
            if (old[i] > r && old[i] < last_digit){
                vis.insert(old[i]);
            }
        }
        
        return (int) vis.size() + (r - l + 1) + (p - 1 - last_digit + 1) == p;
    };

    // bin search 1 -> change the number -> bin search 2
    int l = last_digit, r = p - 1, mid, ans = p - 1;
    bool ok = false;
    while (l <= r){
        mid = (l + r) / 2;
        if (check_before_change(mid)){
            ans = min(ans, mid - last_digit);
            r = mid - 1;
            ok = true;
        }
        else{
            l = mid + 1;
        }
    }

    if (ok){
        cout << ans << "\n";
        return;
    }

    a[n - 1] = 0;
    int carry = 1, ptr = n - 2;
    while (carry && ptr >= 0){
        a[ptr]++;
        carry--;
        if (a[ptr] == p){
            a[ptr] = 0;
            carry++;
        }
        ptr--;
    }
    if (carry){
        a.insert(a.begin(), 1);
    }
    n = a.size();

    l = 0, r = last_digit - 1, ans = p - 1; 
    while (l <= r){
        mid = (l + r) / 2;
        if (check_after_change(mid)){
            ans = min(ans, (p - 1 - last_digit + 1) + mid);
            r = mid - 1;
        }
        else{
            l = mid + 1;
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
