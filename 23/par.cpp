#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 2e5 + 3;

int dp[MAXN][2]; // dp[v][0/1] = max score for a path that goes down from v / v is the LCA of it
vector <int> adj[MAXN];
bool leaf[MAXN], above_leaf[MAXN];

void DFS(int v, int par){
    bool non_leaf_child = false;
    int mx1 = 0, mx2 = 0, children = 0;
    for (int child : adj[v]){
        if (child != par){
            DFS(child, v);
            non_leaf_child |= !leaf[child];
            if (dp[child][0] >= mx1){
                mx2 = mx1;
                mx1 = dp[child][0];
            }
            else if (dp[child][0] >= mx2){
                mx2 = dp[child][0];
            }
            children++;
        }
    }
    if (children == 0){
        leaf[v] = true;
    }
    above_leaf[v] = !non_leaf_child;
    dp[v][0] = max((v == 1 ? 0 : children), mx1 + children - 1);
    dp[v][1] = max(dp[v][0], mx1 + mx2 + children - 2);
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

    DFS(1, 0);

    int ans = 0;
    for (int i = 1; i <= n; i++){
        if (leaf[i]){
            continue;
        }
        else if (above_leaf[i]){
            ans = max(ans, dp[i][1]);
        }
        else{
            ans = max(ans, dp[i][1] + (i != 1));
        }
    }
    cout << ans << "\n";

    return 0;
}   
