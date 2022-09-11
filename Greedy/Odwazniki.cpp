//XIV OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int INF = 1e9 + 3;

// czy da sie upakowac x odwaznikow
bool check(const int &x, const vector <int> &odw, priority_queue <int> pq){
    int ans = 0, max_k;
    for (int i = odw.size() - x; i < (int) odw.size(); i++){
        if (pq.empty()){
            break;
        }
        max_k = pq.top();
        pq.pop();
        if (max_k < odw[i]){
            break;
        }
        else{
            ans++;
            pq.push(max_k - odw[i]);
        }
    }
    return ans >= x;
}

void solve(){
    int n, m, k;
    cin >> n >> m;
    vector <int> odw(m);
    priority_queue <int> pq;
    for (int i = 0; i < n; i++){
        cin >> k;
        pq.push(k);
    }
    for (int i = 0; i < m; i++){
        cin >> odw[i];
    }
    sort(odw.rbegin(), odw.rend());
    int l = 0, r = m, ans = 0, mid;
    while (l <= r){
        mid = (l + r) / 2;
        if (check(mid, odw, pq)){
            l = mid + 1;
            ans = max(ans, mid);
        }
        else{
            r = mid - 1;
        }
    }
    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    //cin >> t;
    while (t--){
        solve();
    }
    return 0;
}   
