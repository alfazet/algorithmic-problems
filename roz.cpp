//XVIII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int INF = 1e9;
int n;
vector <int> occ[26];

int check(const vector <int> &occA, const vector <int> &occB){
    if (occA.empty() || occB.empty()){
        return 0;
    }
    vector <int> merged;
    int i = 0, j = 0;
    while (i < (int) occA.size() && j < (int) occB.size()){
        if (occA[i] < occB[j]){
            merged.push_back(1);
            i++;
        }
        else{
            merged.push_back(-1);
            j++;
        }
    }
    while (i < (int) occA.size()){
        merged.push_back(1);
        i++;
    }
    while (j < (int) occB.size()){
        merged.push_back(-1);
        j++;
    }
    int len = merged.size();
    vector <int> pref;
    pref.push_back(0);
    for (int x : merged){
        pref.push_back(x + pref.back());
    }
    vector <int> min_pref_so_far(len + 1);
    for (int i = 1; i <= len; i++){
        min_pref_so_far[i] = min(min_pref_so_far[i - 1], pref[i]);
    }
    int ans = 0;
    int prev_neg = -1;
    for (int i = 0; i < len; i++){
        if (merged[i] == -1){
            prev_neg = i;
        }
        if (prev_neg != -1){
            ans = max(ans, pref[i + 1] - min_pref_so_far[prev_neg]);
        }
    }
    return ans;
}

void solve(){
    int ans = 0;
    cin >> n;
    string s;
    cin >> s;
    for (int i = 0; i < n; i++){
        occ[s[i] - 'a'].push_back(i);
    }
    for (char i = 0; i <= 25; i++){
        for (int j = 0; j <= 25; j++){
            if (i != j){
                ans = max(ans, check(occ[i], occ[j]));
            }
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
