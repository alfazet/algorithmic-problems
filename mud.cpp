//II OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

void solve(){
    int n, c, d, k, x, all_p_sum = 0;
    lli first_cost = 0;
    cin >> n >> c;
    all_p_sum += c;
    vector <lli> p_pref[n], d_pref[n], dists[n];
    for (int i = 0; i < n; i++){
        p_pref[i].push_back(c);
        d_pref[i].push_back(0);
        cin >> x;
        for (int j = 0; j < x; j++){
            cin >> d >> k;
            all_p_sum += k;
            p_pref[i].push_back(p_pref[i].back() + k);
            d_pref[i].push_back(d_pref[i].back() + d);
            dists[i].push_back(d);
            first_cost += d_pref[i].back() * k;
        }
    }
    lli best = first_cost, cost;
    int len;
    pair <int, int> where = make_pair(0, 0);
    for (int i = 0; i < n; i++){
        cost = first_cost;
        len = p_pref[i].size() - 1;
        for (int j = 1; j <= len; j++){
            cost += (all_p_sum - p_pref[i].back() + p_pref[i][j - 1]) * dists[i][j - 1];
            cost -= (p_pref[i].back() - p_pref[i][j - 1]) * dists[i][j - 1];
            if (cost < best){
                best = cost;
                where = make_pair(i + 1, j);
            }
        }
    }
    cout << best << "\n";
    cout << where.first << " " << where.second << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    //cin >> t;
    t = 1;
    while (t--){
        solve();
    }
    return 0;
}
