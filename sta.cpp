//XV OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int maxn = 1e6 + 3;
int n;
vector <int> adj[maxn];
int sz[maxn];
lli sum_dist[maxn], sum_dist_all[maxn];

void DFS(int v, int par){
    sz[v] = 1;
    for (int child : adj[v]){
        if (child != par){
            DFS(child, v);
            sz[v] += sz[child];
            sum_dist[v] += sum_dist[child] + sz[child];
        }
    }
}

void DFS_reroot(int v, int par){
    if (par != -1){
        sum_dist_all[v] = sum_dist_all[par] + n - 2 * sz[v];
    }
    for (int child : adj[v]){
        if (child != par){
            DFS_reroot(child, v);
        }
    }
}

void solve(){
    int a, b;
    cin >> n;
    for (int i = 0; i < n - 1; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    DFS(1, -1);
    sum_dist_all[1] = sum_dist[1];
    DFS_reroot(1, -1);
    int ans = 1;
    for (int i = 1; i <= n; i++){
        if (sum_dist_all[i] > sum_dist_all[ans]){
            ans = i;
        }
    }
    cout << ans << "\n";
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
