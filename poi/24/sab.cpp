#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 5e5 + 3;

vector <int> adj[MAXN];
int sub_sz[MAXN];
double dp[MAXN];

void DFS(int v){
    sub_sz[v] = 1;
    for (int child : adj[v]){
        DFS(child);
        sub_sz[v] += sub_sz[child];
    }
    for (int child : adj[v]){
        dp[v] = max(dp[v], min(dp[child], sub_sz[child] / (double) (sub_sz[v] - 1)));
    }
    if (sub_sz[v] == 1){
        dp[v] = 1;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k, x;
    cin >> n >> k;
    for (int i = 2; i <= n; i++){
        cin >> x;
        adj[x].push_back(i);
    }
    DFS(1);

    double ans = 0;
    for (int i = 1; i <= n; i++){
        if (sub_sz[i] > k){
            ans = max(ans, dp[i]);
        }
    }
    cout << fixed << setprecision(9) << ans << "\n";

    return 0;
}   
