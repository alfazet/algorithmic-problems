//IOI 2011
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const int MAXN = 2e5 + 3, MAXK = 1e6 + 3, INF = 1e9 + 7;

int n, k, ans, centroid, cur_max, traversed; 
int vis[MAXN], sub_size[MAXN], min_paths[MAXK], dp[MAXK]; // dp[i] = min. ilość krawędzi potrzebna do osiągnięcia długości i

vector <pair <int, int>> adj[MAXN]; 

void DFS_sub_size(int v, int par){
    sub_size[v] = 0;

    for (auto child : adj[v]){
        if (!vis[child.ff] && child.ff != par){
            DFS_sub_size(child.ff, v);
            sub_size[v] += sub_size[child.ff] + 1;
        }
    }
}

void DFS_find_centroid(int v, int par, int total_sz){
    int mx = total_sz - sub_size[v] - 1;

    for (auto child : adj[v]){
        if (!vis[child.ff] && child.ff != par){
            DFS_find_centroid(child.ff, v, total_sz);
            mx = max(mx, sub_size[child.ff] + 1);
        }
    }

    if (mx < cur_max){
        centroid = v;
        cur_max = mx;
    }
}

void DFS_get_ans(int v, int par, int cur_cost, int cur_path_len){
    if (cur_cost > k){
        return;
    }

    if (dp[k - cur_cost] == traversed){
        if (cur_path_len + min_paths[k - cur_cost] < ans || ans == -1){
            ans = cur_path_len + min_paths[k - cur_cost];
        }
    }

    if (cur_cost == k){
        if (cur_path_len < ans || ans == -1){
            ans = cur_path_len;
        }
    }

    for (auto child : adj[v]){
        if (!vis[child.ff] && child.ff != par){
            DFS_get_ans(child.ff, v, cur_cost + child.ss, cur_path_len + 1);
        }
    }
}

void DFS_dp(int v, int par, int cur_cost, int cur_path_len){
    if (cur_cost > k){
        return;
    }

    if (dp[cur_cost] < traversed){
        dp[cur_cost] = traversed;
        min_paths[cur_cost] = cur_path_len;
    }
    else if (cur_path_len < min_paths[cur_cost]){
        dp[cur_cost] = traversed;
        min_paths[cur_cost] = cur_path_len;
    }

    for (auto child : adj[v]){
        if (!vis[child.ff] && child.ff != par){
            DFS_dp(child.ff, v, cur_cost + child.ss, cur_path_len + 1);
        }
    }
}

void DFS_main(int v){
    DFS_sub_size(v, -1);

    if (sub_size[v] <= 1){
        return;
    }

    centroid = -1;
    cur_max = INF;
    DFS_find_centroid(v, -1, sub_size[v] + 1);

    traversed++;
    for (auto child : adj[centroid]){
        if (!vis[child.ff]){
            DFS_get_ans(child.ff, centroid, child.ss, 1);
            DFS_dp(child.ff, centroid, child.ss, 1);
        }
    }
    
    int local_centroid = centroid;
    vis[centroid] = true; 

    for (auto child : adj[local_centroid]){
        if (!vis[child.ff]){
            DFS_main(child.ff);
        }
    }
}

void solve(){
    int a, b, w;
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++){
        cin >> a >> b >> w;
        a++;
        b++;
        adj[a].emplace_back(b, w);
        adj[b].emplace_back(a, w);
    }
    ans = -1;
    DFS_main(1);
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
