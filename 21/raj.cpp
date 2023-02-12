#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 5e5 + 3, BASE = (1 << 19);

int in_deg[MAXN], topo_id[MAXN], from[MAXN], to[MAXN], up_to[MAXN], after[MAXN], over[MAXN], st[2 * BASE + 3];
vector <int> adj[MAXN];
vector <pair <int, int>> edges;

int query(int i){
    i += BASE;
    int ans = st[i];
    while (i > 1){
        i /= 2;
        ans = max(ans, st[i]);
    }
    return ans;
}

void update(int l, int r, int val){
    l += BASE;
    r += BASE;
    st[l] = max(st[l], val);
    if (l != r){
        st[r] = max(st[r], val);
    }
    while (l / 2 != r / 2){
        if (l % 2 == 0){
            st[l + 1] = max(st[l + 1], val);
        }
        if (r % 2 == 1){
            st[r - 1] = max(st[r - 1], val);
        }
        l /= 2;
        r /= 2;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, a, b;
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        edges.emplace_back(a, b);
        in_deg[b]++;
    }

    vector <int> topo;
    queue <int> q;
    for (int i = 1; i <= n; i++){
        if (in_deg[i] == 0){
            q.push(i);
        }
    }
    while (!q.empty()){
        int v = q.front();
        q.pop();
        topo_id[v] = topo.size();
        topo.push_back(v);
        for (int child : adj[v]){
            in_deg[child]--;
            if (in_deg[child] == 0){
                q.push(child);
            }
        }
    }

    for (int i = 0; i < n; i++){
        for (int child : adj[topo[i]]){
            to[topo_id[child]] = max(to[topo_id[child]], to[i] + 1);
        }
    }
    for (int i = 0; i < n; i++){
        up_to[i] = max((i == 0 ? 0 : up_to[i - 1]), to[i]);
    }
    for (int i = n - 1; i >= 0; i--){
        for (int child : adj[topo[i]]){
            from[i] = max(from[i], 1 + from[topo_id[child]]);
        }
    }
    for (int i = n - 1; i >= 0; i--){
        after[i] = max((i == n - 1 ? 0 : after[i + 1]), from[i]);
    }

    for (auto[u, v] : edges){
        if (topo_id[v] - topo_id[u] > 1){
            update(topo_id[u] + 1, topo_id[v] - 1, to[topo_id[u]] + 1 + from[topo_id[v]]);
        }
    }
    for (int i = 0; i < n; i++){
        over[i] = max({query(i), i == 0 ? 0 : up_to[i - 1], i == n - 1 ? 0 : after[i + 1]});
    }

    int ans_remove = 0, ans_len = m;
    for (int i = 0; i < n; i++){
        if (over[i] < ans_len){
            ans_len = over[i];
            ans_remove = topo[i];
        }
    }
    cout << ans_remove << " " << ans_len << "\n";

    return 0;
}   
