#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e5 + 3;

int pre[MAXN], low[MAXN], sub_sz[MAXN], timer = 1, n;
vector <int> adj[MAXN], cut_children[MAXN]; // cut_children[v] = children of v that will become disconnected after removing v
lli ans[MAXN];

void DFS(int v, int par){
    ans[v] = 2 * (n - 1);
    pre[v] = low[v] = timer++;
    sub_sz[v] = 1;
    int children = 0;
    for (int child : adj[v]){
        if (child != par){
            if (pre[child] == 0){
                children++;
                DFS(child, v);
                sub_sz[v] += sub_sz[child];
                low[v] = min(low[v], low[child]);
                if (low[child] >= pre[v]){
                    cut_children[v].push_back(child);
                }
            }
            else{
                low[v] = min(low[v], pre[child]);
            }
        }
    }

    int above = n - 1;
    for (int child : cut_children[v]){
        above -= sub_sz[child];
    }
    for (int child : cut_children[v]){
        ans[v] += 2LL * sub_sz[child] * above; // meetings (this subtree, above) and (above, this subtree)
        ans[v] += 1LL * sub_sz[child] * (n - 1 - above - sub_sz[child]); // meetings (this subtree, some other subtree)
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int m, a, b;
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    DFS(1, -1);

    for (int i = 1; i <= n; i++){
        cout << ans[i] << "\n";
    }

    return 0;
}   
