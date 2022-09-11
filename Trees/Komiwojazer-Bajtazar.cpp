//IX OI 
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 3e4 + 3;

vector <int> adj[MAXN];

struct LCA{
    int n, lg;
    vector <int> depth;
    vector <vector <int>> up; //up[v][i] - (2^i)-th ancestor of v

    void precomp_DFS(int v, int par, int dep){
        for (int child : adj[v]){
            if (child != par){
                depth[child] = dep + 1;
                up[child][0] = v;
                for (int i = 1; i < lg; i++){
                    up[child][i] = up[up[child][i - 1]][i - 1];
                }
                precomp_DFS(child, v, dep + 1);
            }
        }
    }

    void init(int n_){
        n = n_;
        lg = 0;
        while ((1 << lg) < n){
            lg++;
        }
        up.assign(n + 1, vector <int>(lg, 0));
        depth.assign(n + 1, 0);
        precomp_DFS(1, -1, 0);
    }

    int find_LCA(int u, int v){
        if (depth[u] < depth[v]){ //u is deeper
            swap(u, v);
        }
        int diff = depth[u] - depth[v];

        for (int i = lg - 1; i >= 0; i--){
            if (diff & (1 << i)){
                u = up[u][i];
            }
        }

        if (u == v){
            return u;
        }

        for (int i = lg - 1; i >= 0; i--){
            if (up[u][i] != up[v][i]){
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

    int get_dist(int u, int v){
        return depth[u] + depth[v] - 2 * depth[find_LCA(u, v)];
    }
};

void solve(){
    int n, a, b, q, v;
    cin >> n;
    for (int i = 0; i < n - 1; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    LCA lca;
    lca.init(n);

    cin >> q;
    int pre = 1;
    lli ans = 0;
    while (q--){
        cin >> v;
        ans += lca.get_dist(pre, v);
        pre = v;
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
