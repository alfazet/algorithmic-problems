//VII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 5003;

int n, ans = 0;
vector <int> adj[MAXN];
bool vis[MAXN];

void DFS(int v){
    if (v == n){
        ans++;
        return;
    }
    else{
        vis[v] = true;
    }
    for (int child : adj[v]){
        if (!vis[child]){
            DFS(child);
            break;
        }
    }
}

void solve(){
    int k, v;
    cin >> n;
    for (int i = 1; i <= n - 1; i++){
        cin >> k;
        for (int j = 0; j < k; j++){
            cin >> v;
            adj[i].push_back(v);
        }
    }
    for (int child : adj[1]){
        if (!vis[child]){
            DFS(child);
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
