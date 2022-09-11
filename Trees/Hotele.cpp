//XXI OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int maxn = 5003;

vector <int> adj[maxn];

void DFS(vector <int> &count_at_dep, int v, int par, int depth){
    if ((int) count_at_dep.size() < depth + 1){
        count_at_dep.resize(depth + 1, 0);
    }
    count_at_dep[depth]++;
    for (int child : adj[v]){
        if (child != par){
            DFS(count_at_dep, child, v, depth + 1);
        }
    }
}

lli add(vector <vector <int>> depths){
    lli out = 0;

    vector <int> all;
    for (int i = 0; i < (int) depths.size(); i++){
        if ((int) all.size() < (int) depths[i].size()){
            all.resize(depths[i].size(), 0);
        }
        for (int j = 0; j < (int) depths[i].size(); j++){
            all[j] += depths[i][j];
        }
    }
    lli cnt;
    for (int i = 0; i < (int) all.size(); i++){
        cnt = all[i];
        out += cnt * (cnt - 1) * (cnt - 2) / 6;
    }
    for (int i = 0; i < (int) depths.size(); i++){
        for (int j = 0; j < (int) depths[i].size(); j++){
            cnt = depths[i][j];
            out -= cnt * (cnt - 1) * (all[j] - cnt) / 2;
            out -= cnt * (cnt - 1) * (cnt - 2) / 6;
        }
    }
    return out;
}

void solve(){
    int n, a, b;
    lli ans = 0;
    cin >> n;
    for (int i = 0; i < n - 1; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    //re-rooting
    for (int i = 1; i <= n; i++){
        vector <vector <int>> depths_of_subs(adj[i].size());
        for (int j = 0; j < (int) adj[i].size(); j++){
            DFS(depths_of_subs[j], adj[i][j], i, 0);
        }
        ans += add(depths_of_subs);
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
