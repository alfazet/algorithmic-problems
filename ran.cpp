//XIX OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 5e5 + 3, LOG = 19;

int nxt[MAXN], cc[MAXN], cycle[MAXN], tree[MAXN], depth[MAXN], up[MAXN][LOG], pos_in_cycle[MAXN], cycle_sz[MAXN], cc_no, cycle_no, tree_no;
bool vis[MAXN];
vector <int> adj[MAXN], adj_t[MAXN], children[MAXN], cur_cycle;

void find_cycle(int v){
    vis[v] = true;
    while (!vis[nxt[v]]){
        v = nxt[v];
        vis[v] = true;
    }
    int i = 1;
    cur_cycle.push_back(v);
    pos_in_cycle[v] = i++;
    cycle[v] = cycle_no;
    int start = v;
    while (nxt[v] != start){
        v = nxt[v];
        cur_cycle.push_back(v);
        pos_in_cycle[v] = i++;
        cycle[v] = cycle_no;
    }
}

void DFS_t(int v, int par){
    tree[v] = tree_no;
    for (int child : adj_t[v]){
        if (child != par && cycle[child] == 0){
            children[v].push_back(child);
            DFS_t(child, v);
        }
    }
}

void DFS_cc(int v){
    vis[v] = true;
    cc[v] = cc_no;
    for (int child : adj[v]){
        if (!vis[child]){
            DFS_cc(child);
        }
    }
}

void precomp_LCA(int v, int dep){
    for (int child : children[v]){
        depth[child] = dep + 1;
        up[child][0] = v;
        for (int i = 1; i < LOG; i++){
            up[child][i] = up[up[child][i - 1]][i - 1];
        }
        precomp_LCA(child, dep + 1);
    }
}

int find_LCA(int u, int v){
    if (depth[u] < depth[v]){ //u is deeper
        swap(u, v);
    }
    int diff = depth[u] - depth[v];

    for (int i = LOG - 1; i >= 0; i--){
        if (diff & (1 << i)){
            u = up[u][i];
        }
    }

    if (u == v){
        return u;
    }

    for (int i = LOG - 1; i >= 0; i--){
        if (up[u][i] != up[v][i]){
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

bool better(pair <int, int> p1, pair <int, int> p2){
    int mx1 = max(p1.first, p1.second), mn1 = min(p1.first, p1.second), mx2 = max(p2.first, p2.second), mn2 = min(p2.first, p2.second);
    if (mx1 == mx2){
        if (mn1 == mn2){
            return p1.second < p2.second;
        }
        else{
            return mn1 < mn2;
        }
    }
    else{
        return mx1 < mx2;
    }
}

void solve(){
    int n, q, x, y, lc, ans_x, ans_y, x_to_y, y_to_x, diff;
    cin >> n >> q;
    for (int i = 1; i <= n; i++){
        cin >> nxt[i];
        adj[i].push_back(nxt[i]);
        adj[nxt[i]].push_back(i);
        adj_t[nxt[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++){
        if (!vis[i]){
            cc_no++;
            DFS_cc(i);
        }
    }
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++){
        if (cycle[i] == 0 && tree[i] == 0){
            cycle_no++;
            find_cycle(i);
            for (int v : cur_cycle){
                tree_no = v;
                DFS_t(v, -1);
                precomp_LCA(v, 0);
            }
            cycle_sz[cycle_no] = cur_cycle.size();
            cur_cycle.clear();
        }
    }
    while (q--){
        cin >> x >> y;
        if (cc[x] != cc[y]){
            cout << "-1 -1\n";
        }
        else if (tree[x] == tree[y]){
            lc = find_LCA(x, y);
            cout << depth[x] - depth[lc] << " " << depth[y] - depth[lc] << "\n";
        }
        else{
            ans_x = depth[x], ans_y = depth[y];
            x = tree[x], y = tree[y];
            x_to_y = pos_in_cycle[y] - pos_in_cycle[x];
            if (x_to_y < 0){
                x_to_y = cycle_sz[cycle[x]] + x_to_y;
            }
            y_to_x = cycle_sz[cycle[x]] - x_to_y;
            pair <int, int> opt1 = {ans_x + x_to_y, ans_y}, opt2 = {ans_x, ans_y + y_to_x};
            if (better(opt1, opt2)){
                cout << opt1.first << " " << opt1.second << "\n";
            }
            else{
                cout << opt2.first << " " << opt2.second << "\n";
            }
        }
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
