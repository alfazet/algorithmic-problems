#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 3e5 + 3;

int dp[MAXN], builders; // dp[i] - min arches required in the subtree of i when the king is entering i
vector <int> adj[MAXN];

void DFS(int v, int par){
    for (int child : adj[v]){
        if (child != par){
            DFS(child, v);
            dp[v] += dp[child];
        }
    }
    dp[v] = max(0, dp[v] - builders) + 1;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int n, a, b;
    cin >> n;
    for (int i = 0; i < n - 1; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    auto check = [&](int k){
        builders = k;
        memset(dp, 0, sizeof(dp));
        DFS(1, -1);
        return dp[1] <= 1;
    };

    int l = 0, r = n, mid, ans = r;
    while (l <= r){
        mid = (l + r) / 2;
        if (check(mid)){
            ans = min(ans, mid);
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    cout << ans << "\n";

    return 0;
}
