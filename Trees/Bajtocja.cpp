//I OIG
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 7007, MAXM = 3e5 + 7, LOG = 14;

struct Edge{
    int u, v, wgt, no;

    bool operator < (Edge e){
        return wgt < e.wgt;
    }
};

vector <Edge> adj_mst[MAXN];
vector <Edge> edges;
int par[MAXN], sz[MAXN], depth[MAXN], jump[MAXN][LOG], jump_max[MAXN][LOG]; // jump_max[v][i] = max. na ścieżce od v do jump[v][i]
bool in_MST[MAXM], ans[MAXM];

int find(int a){
    if (par[a] == a){
        return a;
    }
    return par[a] = find(par[a]);
}

void merge(int a, int b){
    a = find(a);
    b = find(b);
    if (sz[b] > sz[a]){
        swap(a, b);
    }
    sz[a] += sz[b];
    par[b] = a;
}

void DFS_LCA_precomp(int v, int par, int dep){
    jump[v][0] = par;
    depth[v] = dep;
    for (Edge e : adj_mst[v]){
        if (e.u == v && e.v != par){
            jump_max[e.v][0] = e.wgt;
            DFS_LCA_precomp(e.v, v, dep + 1);
        }
        else if (e.v == v && e.u != par){
            jump_max[e.u][0] = e.wgt;
            DFS_LCA_precomp(e.u, v, dep + 1);
        }
    }
}

int find_max_on_path(int u, int v){ 
    int mx = 0;

    if (depth[u] < depth[v]){
        swap(u, v);
    }
    int diff = depth[u] - depth[v];
    for (int i = 1; i < LOG; i++){
        if (diff & (1 << i)){
            mx = max(mx, jump_max[u][i]);
            u = jump[u][i];
        }
    }
    if (u == v){
        return mx;
    }
    for (int i = 1; i < LOG; i++){
        if (jump[u][i] != jump[v][i]){
            mx = max(mx, jump_max[u][i]);
            mx = max(mx, jump_max[v][i]);
            u = jump[u][i];
            v = jump[v][i];
        }
    }
    return max({mx, jump_max[u][0], jump_max[v][0]});
} 

void solve(){
    int n, m, a, b, w;
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        sz[i] = 1;
        par[i] = i;
    }
    for (int i = 0; i < m; i++){
        cin >> a >> b >> w;
        edges.push_back({a, b, w, i});
    }

    sort(edges.begin(), edges.end());
    for (Edge e : edges){
        if (find(e.u) != find(e.v)){
            in_MST[e.no] = true;
            merge(e.u, e.v);
            adj_mst[e.u].push_back(e);
            adj_mst[e.v].push_back(e);
        }
    }

    DFS_LCA_precomp(1, 0, 0);
    for (int i = 1; i < LOG; i++){
        for (int v = 1; v <= n; v++){
            jump[v][i] = jump[jump[v][i - 1]][i - 1];
            jump_max[v][i] = max(jump_max[v][i - 1], jump_max[jump[v][i - 1]][i - 1]);
        }
    }

    for (Edge e : edges){
        if (in_MST[e.no]){
            ans[e.no] = true;
            continue;
        }
        int mx = find_max_on_path(e.u, e.v);
        //cout << "max on path " << e.u << " " << e.v << " = " << mx << "\n";
        if (mx == e.wgt){
            ans[e.no] = true;
        }
    }

    for (int i = 0; i < m; i++){
        cout << (ans[i] ? "TAK\n" : "NIE\n");
    }
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
