//XXI OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 5e5 + 3;

vector <int> adj[MAXN];
lli instal[MAXN], dp[MAXN], sz[MAXN];

bool comp(int v1, int v2){
    return dp[v1] - sz[v1] > dp[v2] - sz[v2];
}

void DFS1(int v, int par){
    for (int child : adj[v]){
        if (child != par){
            DFS1(child, v);
            sz[v] += 2 + sz[child];
        }
    }
}

void DFS2(int v, int par){
    dp[v] = instal[v];
    for (int child : adj[v]){
        if (child != par){
            DFS2(child, v);
        }
    }
    sort(adj[v].begin(), adj[v].end(), comp);
    lli in = 1;
    for (int child : adj[v]){
        if (child != par){
            dp[v] = max(dp[v], dp[child] + in);
            in += 2 + sz[child];
        }
    }
}

void solve(){
    int n, a, b;
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> instal[i];
    }
	for (int i = 0; i < n - 1; i++){
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
    DFS1(1, -1);
    DFS2(1, -1);
    cout << max(dp[1], instal[1] + sz[1]) << "\n";
}

int main(){
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
