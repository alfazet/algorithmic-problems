#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e5 + 3;

vector <pair <int, lli>> adj[MAXN];
lli d[MAXN], h[MAXN]; 
int highest_child[MAXN], p[MAXN];

void DFS(int v, int par, lli dep){
    d[v] = dep;
    p[v] = par;
    for (auto[child, w] : adj[v]){
        if (child != par){
            DFS(child, v, dep + w);
            if (h[child] + w > h[v]){
                highest_child[v] = child;
                h[v] = h[child] + w;
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int n, k, a, b, w;
    lli ans = 0;
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++){
        cin >> a >> b >> w;
        ans += 2 * w;
        adj[a].emplace_back(b, w);
        adj[b].emplace_back(a, w);
    }

    DFS(1, 0, 0);

    priority_queue <pair <lli, int>> pq;
    pq.emplace(h[1], 1);
    for (int i = 0; i < k; i++){
        if (pq.empty()) break;
        auto[len, v] = pq.top();
        pq.pop();
        if (len <= 0) break;

        ans -= len;
        int u = v;
        while (h[u] > 0){
            for (auto[child, w] : adj[u]){
                if (child != p[u] && child != highest_child[u]){
                    pq.emplace(h[child] + w - d[u], child);
                }
            }
            u = highest_child[u];
        }
    }
    cout << ans << "\n";

    return 0;
}   
