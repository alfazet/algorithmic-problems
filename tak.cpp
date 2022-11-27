//XX OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

void solve(){
    lli dest, base;
    int n;
    cin >> dest >> base >> n;
    vector <lli> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.rbegin(), a.rend());

    lli chosen = 0, excess = 0, earliest = base;
    int taken_id;
    if (a[0] >= base + dest){
        cout << "1\n";
        return;
    }
    
    //if we made it here, we can't do one taxi
    vector <lli> :: iterator it = upper_bound(a.begin(), a.end(), dest - base, greater <lli>()); //check if we can go base - end with anything//
    if (it == a.begin()){
        cout << "0\n";
        return;
    }
    else{
        it--;
        taken_id = it - a.begin();
        chosen = *it; //a taxi that can take us from base to the end
        if (chosen > dest - base){
            excess = (chosen - (dest - base)) / 2; //additional distance that taxi can travel back from the base
        }
        earliest = base - excess;
    }

    lli pos = 0, ans = 1;
    int i = 0;
    while (pos < earliest){
        if (i == taken_id){
            i++;
        }
        if (i >= n){
            cout << "0\n";
            return;
        }
        if (base - pos >= a[i]){
            cout << "0\n";
            return;
        }
        pos += a[i] - (base - pos);
        i++;
        ans++;
    }
    if (pos >= dest){
        ans--;
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
