#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e6 + 3;

vector <int> adj[MAXN];
int sub_sz[MAXN], n; 
lli sum_dist_sub[MAXN], sum_dist_all[MAXN]; // sums of distances: to all nodes in the subtree / all other nodes

void DFS(int v, int par){
    sub_sz[v] = 1;
    for (int child : adj[v]){
        if (child != par){
            DFS(child, v);
            sum_dist_sub[v] += sum_dist_sub[child] + sub_sz[child]; 
            sub_sz[v] += sub_sz[child];
        }
    }
}

void DFS_reroot(int v, int par){
    for (int child : adj[v]){
        if (child != par){
            sum_dist_all[child] = sum_dist_all[v] - sub_sz[child] + (n - sub_sz[child]);
            DFS_reroot(child, v);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b;
    cin >> n;
    for (int i = 0; i < n - 1; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    DFS(1, -1);
    sum_dist_all[1] = sum_dist_sub[1];
    DFS_reroot(1, -1);

    int ans = 1;
    for (int i = 1; i <= n; i++){
        if (sum_dist_all[i] > sum_dist_all[ans]){
            ans = i;
        }
    }
    cout << ans << "\n";

    return 0;
}
