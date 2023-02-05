#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e5 + 3, MOD = 1e9 + 7, LOG = 18;

vector <pair <int, int>> adj[MAXN];
int cycle[MAXN], depth[MAXN], sz[MAXN], pre[MAXN], low[MAXN], big_cnt[MAXN], up[MAXN][LOG], timer = 1, c_id = 0;
pair <int, int> edge[MAXN];
vector <int> adj_c[MAXN]; // adj_c = adjacency list for the decomposition tree
bool bridge[MAXN], any_bridge = false;
lli p2[MAXN];

lli mmul(lli a, lli b){
    return (a * b) % MOD;
}

void DFS(int v, int par){ // find bridges
    pre[v] = low[v] = timer++;
    for (auto[child, id] : adj[v]){
        if (child != par){
            if (pre[child] == 0){
                DFS(child, v);
                low[v] = min(low[v], low[child]);
                if (low[child] > pre[v]){
                    bridge[id] = true;
                    any_bridge = true;
                }
            }
            else{
                low[v] = min(low[v], pre[child]);
            }
        }
    }
}

void DFS2(int v, int par){ // decompose into cycles
    cycle[v] = c_id;
    sz[c_id]++;
    for (auto[child, id] : adj[v]){
        if (child != par){
            if (!bridge[id] && cycle[child] == 0){
                DFS2(child, v);
            }
        }
    }
}

void DFS3(int v, int par, int dep, int big){ // prepare for LCA
    depth[v] = dep;
    up[v][0] = par;
    big += (sz[v] > 1);
    big_cnt[v] = big;
    for (int child : adj_c[v]){
        if (child != par){
            DFS3(child, v, dep + 1, big);
        }
    }
}

int LCA(int u, int v){
    if (depth[u] < depth[v]){
        swap(u, v);
    }
    int d = depth[u] - depth[v];
    for (int b = 0; b <= LOG - 1; b++){
        if (d & (1 << b)){
            u = up[u][b];
        }
    }
    if (u == v){
        return u;
    }

    for (int b = LOG - 1; b >= 0; b--){
        if (up[u][b] != up[v][b]){
            u = up[u][b];
            v = up[v][b];
        }
    }
    return up[u][0];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, a, b, q;
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a].emplace_back(b, i);
        adj[b].emplace_back(a, i);
        edge[i] = {a, b};
    }

    DFS(1, 0);
    for (int i = 0; i < m; i++){
        if (bridge[i]){
            if (cycle[edge[i].first] == 0){
                c_id++;
                DFS2(edge[i].first, 0);
            }
            if (cycle[edge[i].second] == 0){
                c_id++;
                DFS2(edge[i].second, 0);
            }
        }
    }
    if (!any_bridge){ // edge case
        for (int i = 1; i <= n; i++){
            cycle[i] = 1;
        }
        sz[1] = n;
    }
    for (int i = 0; i < m; i++){
        a = cycle[edge[i].first], b = cycle[edge[i].second];
        if (a != b){
            adj_c[a].push_back(b);
            adj_c[b].push_back(a);
        }
    }
    DFS3(1, 0, 0, 0);

    for (int b = 1; b <= LOG - 1; b++){
        for (int i = 1; i <= c_id; i++){
            up[i][b] = up[up[i][b - 1]][b - 1];
        }
    }

    p2[0] = 1;
    for (int i = 1; i <= n; i++){
        p2[i] = mmul(p2[i - 1], 2);
    }
    cin >> q;
    while (q--){
        cin >> a >> b;
        a = cycle[a];
        b = cycle[b];
        int l = LCA(a, b);
        cout << p2[big_cnt[a] + big_cnt[b] - 2 * big_cnt[l] + (sz[l] > 1 ? 1 : 0)] << "\n";
    }

    return 0;
}   
