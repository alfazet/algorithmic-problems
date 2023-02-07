#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 2e4 + 3;

int topo[2 * MAXN], cc[2 * MAXN], in_deg[2 * MAXN], cc_cnt = 0;
vector <int> adj[2 * MAXN][2][2], post; // [0/1][0/1] = normal/transposed and normal/condensed
bool vis[2 * MAXN], val[2 * MAXN];

void DFS(int v){
    vis[v] = true;
    for (int child : adj[v][0][0]){
        if (!vis[child]){
            DFS(child);
        }
    }
    post.push_back(v);
}

void DFS2(int v){
    cc[v] = cc_cnt;
    for (int child : adj[v][1][0]){
        if (cc[child] == 0){
            DFS2(child);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, a, b;
    cin >> n >> m;
    n *= 2;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a][0][0].push_back(b + MAXN); // ~a = a + MAXN
        adj[a + MAXN][1][0].push_back(b);
        adj[b][0][0].push_back(a + MAXN);
        adj[b + MAXN][1][0].push_back(a);
    }
    for (int i = 1; i <= n; i += 2){
        adj[i + MAXN][0][0].push_back(i + 1);
        adj[i + 1][1][0].push_back(i + MAXN);
        adj[i + 1 + MAXN][0][0].push_back(i);
        adj[i][1][0].push_back(i + 1 + MAXN);
    }

    for (int i = 1; i <= n; i++){
        if (!vis[i]){
            DFS(i);
        }
        if (!vis[i + MAXN]){
            DFS(i + MAXN);
        }
    }
    reverse(post.begin(), post.end());
    for (int v : post){
        if (cc[v] == 0){
            cc_cnt++;
            DFS2(v);
        }
    }

    for (int i = 1; i <= n; i++){
        if (cc[i] == cc[i + MAXN]){
            cout << "NIE\n";
            return 0;
        }
    }

    for (int i = 1; i <= n; i++){
        for (int child : adj[i][0][0]){
            if (cc[i] != cc[child]){
                adj[cc[i]][0][1].push_back(cc[child]);
                in_deg[cc[child]]++;
            }
        }
        for (int child : adj[i + MAXN][0][0]){
            if (cc[i + MAXN] != cc[child]){
                adj[cc[i + MAXN]][0][1].push_back(cc[child]);
                in_deg[cc[child]]++;
            }
        }
    }

    queue <int> q;
    for (int i = 1; i <= cc_cnt; i++){
        if (in_deg[i] == 0) q.push(i);
    }

    int p = 0;
    while (!q.empty()){
        int v = q.front();
        q.pop();
        topo[v] = p++;
        for (int child : adj[v][0][1]){
            in_deg[child]--;
            if (in_deg[child] == 0){
                q.push(child);
            }
        }
    }

    for (int i = 1; i <= n; i += 2){
        if (topo[cc[i]] < topo[cc[i + MAXN]]){ // set i to false as it comes before ~i in the chain of implications (false => true, but true !=> false)
            cout << i + 1 << "\n";
        }
        else{
            cout << i << "\n";
        }
    }

    return 0;
}   
