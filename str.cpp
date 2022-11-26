//XXIV OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 5e5 + 3;

vector <int> adj[MAXN];
bool on_strike[MAXN], is_leaf[MAXN];
int ok_children[MAXN], deg[MAXN], parent[MAXN];

void DFS(int v, int par){
    parent[v] = par;
    if (adj[v].size() == 1){
        is_leaf[v] = true;
    }
    for (int child : adj[v]){
        if (child != par){
            DFS(child, v);
            ok_children[v]++;
        }
    }
}

void solve(){
    int n, a, b, q, v, ccs = 1;
    cin >> n;
    for (int i = 0; i < n - 1; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        deg[a]++;
        deg[b]++;
    }
    DFS(1, 0);
    on_strike[0] = true;
    cin >> q;
    while (q--){
        cin >> v;
        if (v > 0){
            on_strike[v] = true;
            ok_children[parent[v]]--;
            ccs += ok_children[v] - 1 + !on_strike[parent[v]];
        }
        else{
            v = -v;
            on_strike[v] = false;
            ok_children[parent[v]]++;
            ccs -= ok_children[v] - 1 + !on_strike[parent[v]];
        }
        cout << ccs << "\n";
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
