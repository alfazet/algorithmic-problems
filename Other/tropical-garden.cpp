// IOI 2011
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1.5e5 + 3, INF = 1e9 + 3;

int in[MAXN], nxt[2 * MAXN], dist[2 * MAXN][2], X, cycle_len_1 = INF, cycle_len_2 = INF; // dist[v][0/1] - dist(v, X/X')
vector <int> adj[2 * MAXN]; // v = we just started or entered v not from the best edge, v' = v + MAXN = we entered v from the best edge
bool vis[2 * MAXN][2];

void DFS(int v, int t, int d){
    vis[v][t] = true;
    dist[v][t] = d;
    for (int child : adj[v]){
        if (!vis[child][t]){
            DFS(child, t, d + 1);
        }
        if (t == 0 && child == X){
            cycle_len_1 = d + 1;
            continue;
        }
        if (t == 1 && child == X + MAXN){
            cycle_len_2 = d + 1;
            continue;
        }
    }
}

int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, a, b;
    cin >> n >> m >> X;
    X++;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        a++;
        b++;

        if (in[a] == 0){ 
            if (in[b] == 0){ 
                nxt[b] = a + MAXN;
            }
            else{ 
                if (nxt[b + MAXN] == 0){
                    nxt[b + MAXN] = a + MAXN;
                }
            }
        }
        else{ 
            if (in[b] == 0){ 
                nxt[b] = a;
            }
            else{ 
                if (nxt[b + MAXN] == 0){
                    nxt[b + MAXN] = a;
                }
            }
        }

        if (in[b] == 0){
            if (in[a] == 0){ 
                nxt[a] = b + MAXN;
            }
            else{ 
                if (nxt[a + MAXN] == 0){
                    nxt[a + MAXN] = b + MAXN;
                }
            }
        }
        else{ 
            if (in[a] == 0){ 
                nxt[a] = b;
            }
            else{
                if (nxt[a + MAXN] == 0){
                    nxt[a + MAXN] = b;
                }
            }
        }
        in[a]++;
        in[b]++;
    }

    for (int i = 1; i <= n; i++){
        if (in[i] == 1){
            if (nxt[i] != 0){
                nxt[i + MAXN] = nxt[i];
            }
            else{
                nxt[i] = nxt[i + MAXN];
            }
        }
        adj[nxt[i]].push_back(i);
        adj[nxt[i + MAXN]].push_back(i + MAXN);
        dist[i][0] = INF;
        dist[i + MAXN][0] = INF;
        dist[i][1] = INF;
        dist[i + MAXN][1] = INF;
    }


    DFS(X, 0, 0); // DFS backwards from X
    DFS(X + MAXN, 1, 0);
    
    int Q, ans, k;
    cin >> Q;
    while (Q--){
        ans = 0;
        cin >> k;
        for (int i = 1; i <= n; i++){
            if (dist[i][0] == k || (dist[i][0] != INF && cycle_len_1 != INF && k > dist[i][0] && (k - dist[i][0]) % cycle_len_1 == 0)){
                ans++;
            }
            if (dist[i][1] == k || (dist[i][1] != INF && cycle_len_2 != INF && k > dist[i][1] && (k - dist[i][1]) % cycle_len_2 == 0)){
                ans++;
            }
        }
        cout << ans << " ";
    }
    cout << "\n";

    return 0;
}
