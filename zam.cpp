//IX OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int maxn = 103, maxx = 1003;

vector <int> adj[maxn];
bool vis[maxn][maxx];
int cost[maxn], n, m, a, b, start, last, x;
pair <int, int> prv[maxn][maxx], nowy;

//od tylu
void BFS(pair <int, int> v){
    queue <pair <int, int>> q;
    q.push(v);
    while (!q.empty()){
        v = q.front();
        q.pop();
        int where = v.first, money = v.second;
        if (where == start && money == x){
            return;
        }
        for (int child : adj[where]){
            if (money + cost[child] > x){
                continue;
            }
            if (!vis[child][money + cost[child]]){
                nowy.first = child;
                nowy.second = money + cost[child];
                vis[child][money + cost[child]] = true;
                prv[child][money + cost[child]] = {where, money};
                q.push(nowy);
            }
        }
    }
}

void solve(){
    cin >> n >> m >> start >> last >> x;
    for (int i = 1; i <= n; i++){
        cin >> cost[i];
    }
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    BFS({last, cost[last]});

    cout << start << " ";
    pair <int, int> temp = prv[start][x];
    while (temp.first != 0){
        cout << temp.first << " ";
        temp = prv[temp.first][temp.second];
    }
    cout << "\n";
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
