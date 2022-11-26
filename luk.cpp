//XX OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 3e5 + 7;

int k;
vector <int> adj[MAXN];
int dp[MAXN]; // ile łuków trzeba zbudować przed wejściem króla do v

void DFS(int v, int par){ // mamy k ekip
    int trzeba = 0;
    for (int child : adj[v]){
        if (child != par){
            DFS(child, v);
            trzeba += dp[child] + 1;
        }
    }
    trzeba -= k; // używamy k ekip w tej "rundzie"
    dp[v] = max(trzeba, 0);
}

void solve(){
    int n, a, b;
    cin >> n;
    for (int i = 0; i < n - 1; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int l = 0, r = n, mid, ans = n;
    while (l <= r){
        mid = (l + r) / 2;
        k = mid;
        DFS(1, -1); // czy można z k ekipami
        if (dp[1] == 0){
            r = mid - 1;
            ans = min(ans, mid);
        }
        else{
            l = mid + 1;
        }
        memset(dp, 0, sizeof(dp));
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
