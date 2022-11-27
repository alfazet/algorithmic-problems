//VIII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

bool comp(pair <int, int> &a, pair <int, int> &b){
    if (a.second < b.second){
        return true;
    }
    return a.first < b.first;
}

void solve(){
    int n;
    cin >> n;
    vector <pair <int, int>> a(n), ans;
    for (int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end());
    int low = a[0].first, high = a[0].second, l, r;
    for (int i = 1; i < n; i++){
        l = a[i].first;
        r = a[i].second;
        if (l > high){
            ans.push_back({low, high});
            low = l;
            high = r;
        }
        else{
            high = max(high, r);
        }
    }
    ans.push_back({low, high});
    for (pair <int, int> p : ans){
        cout << p.first << " " << p.second << "\n";
    }
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
