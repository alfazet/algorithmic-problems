//XXV OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 5e4 + 3;

vector <int> adj[MAXN], adj_t[MAXN], adj_cc[MAXN];
int comp[MAXN], comp_sz[MAXN], dp[MAXN];
bool vis[MAXN], vis_cc[MAXN];

int cc_no = 0;
vector <int> postorder;

void DFS_postorder(int v){
    vis[v] = true;
    for (int child : adj[v]){
        if (!vis[child]){
            DFS_postorder(child);
        }
    }
    postorder.push_back(v);
}

void DFS_trans(int v){ 
    comp[v] = cc_no;
    comp_sz[cc_no]++;
    for (int child : adj_t[v]){
        if (comp[child] == 0){
            DFS_trans(child);
        }
        else if (comp[child] != cc_no){
            adj_cc[comp[child]].push_back(cc_no);
        }
    }
}

void DFS_dp(int v, int par){
    vis_cc[v] = true;
    dp[v] = comp_sz[v];
    for (int child : adj_cc[v]){
        if (child != par){
            DFS_dp(child, v);
            dp[v] += dp[child];
        }
    }
}

void solve(){
	int n, m, a, b;
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj_t[b].push_back(a);
    }
    
    for (int i = 1; i <= n; i++){
        if (!vis[i]){
            DFS_postorder(i);
        }
    }
    reverse(postorder.begin(), postorder.end());
    for (int i = 0; i < n; i++){
        if (comp[postorder[i]] == 0){
            cc_no++;
            DFS_trans(postorder[i]);
        }
    }
    
    for (int i = 1; i <= n; i++){
        if (!vis_cc[i]){
            DFS_dp(i, -1);
        }
    }
    for (int i = 1; i <= n; i++){
        cout << dp[comp[i]] - 1 << "\n";
    }
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	int t;
	t = 1;
	//cin >> t;
	while (t--){
		solve();
	}
	return 0;
}
