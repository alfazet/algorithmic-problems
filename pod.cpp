//XXIV OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

lli query(const vector <lli> &a, lli k){
    return (lower_bound(a.begin(), a.end(), k) - a.begin());
}

void solve(){
    lli b, q;
    lli k;
    cin >> b >> q;
    vector <lli> amount(b);
    lli digSum = 0;
    for (lli i = 0; i < b; i++){
        cin >> amount[i];
        digSum += amount[i] * i;
    }
    if (digSum % (b - 1) != 0){
        amount[digSum % (b - 1)]--;
    }
    vector <lli> pref(b);
    pref[0] = amount[0] - 1;
    for (lli i = 1; i < b; i++){
        pref[i] = pref[i - 1] + amount[i];
    }
    while (q--){
        cin >> k;
        lli ans = query(pref, k);
        cout << (ans < b ? ans : -1) << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int t;
    //cin >> t;
    t = 1;
    while (t--){
        solve();
    }
    return 0;
}
