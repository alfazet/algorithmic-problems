#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 5003;

vector <int> adj[MAXN], traversal;

void DFS(int par, int v, int parity){
    if (parity == 0){
        traversal.push_back(v);
    }
    for (int child : adj[v]){
        if (child != par){
            DFS(v, child, parity ^ 1);
        }
    }
    if (parity == 1){
        traversal.push_back(v);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a, b;
    cin >> n;
    for (int i = 0; i < n - 1; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    DFS(0, 1, 0);
    for (int x : traversal){
        cout << x << "\n";
    }

    return 0;
}   
