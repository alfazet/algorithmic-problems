//VII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int maxn = 252;

int moves = 0;
vector <int> adj[maxn];
bool vis1[maxn][maxn], vis2[maxn][maxn];
int dist[maxn][maxn];

bool BFS(pair <int, int> state){
    queue <pair <int, int>> q1;
    q1.push(state);
    vis1[state.first][state.second] = true;
    while (!q1.empty()){
        queue <pair <int, int>> q2;
        while (!q1.empty()){
            pair <int, int> state = q1.front();
            q1.pop();
            int u = state.first, v = state.second; 
            if (u == v){
                cout << moves;
                return true;
            }
            for (int child : adj[u]){
                if (!vis2[child][v]){
                    vis2[child][v] = true;
                    q2.push(make_pair(child, v));
                }
            }
        }
        while (!q2.empty()){
            pair <int, int> state = q2.front();
            q2.pop();
            int u = state.first, v = state.second; 
            for (int child : adj[v]){
                if (!vis1[u][child]){
                    vis1[u][child] = true;
                    q1.push(make_pair(u, child));
                }
            }
        }
        moves++;
    }
    return false;
}

void solve(){
    int n, m, sa, sb, a, b;
    cin >> n >> m;
    cin >> sa >> sb;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a].push_back(b);
    }
    bool ok = BFS(make_pair(sa, sb));
    cout << (ok ? "\n" : "NIE\n");
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
