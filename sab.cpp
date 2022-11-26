//XXIV OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int maxn = 5e5 + 3;

vector <int> desc[maxn];
int sub_sz[maxn];
double dp[maxn];

void DFS(int v){
    sub_sz[v] = 1;
    if (desc[v].empty()){
        dp[v] = 1.0;
        return;
    }
    dp[v] = 0.0;
    for (int child : desc[v]){
        DFS(child);
        sub_sz[v] += sub_sz[child];
    }
    for (int child : desc[v]){
        dp[v] = max(dp[v], min(dp[child], (double) sub_sz[child] / (sub_sz[v] - 1)));
    }
}

void solve(){
    int n, k, x;
    cin >> n >> k;
    for (int i = 2; i <= n; i++){
        cin >> x;
        desc[x].push_back(i);
    }
    DFS(1);
    double ans = 0.0;
    for (int i = 1; i <= n; i++){
        if (sub_sz[i] > k){
            ans = max(ans, dp[i]);
        }
    }
    cout << fixed << setprecision(10) << ans << "\n";
}

int main(){
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
