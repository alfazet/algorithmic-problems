//XV OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e5 + 3;
vector <int> adj[MAXN];
int in[MAXN], low[MAXN], n, timer;
lli ans[MAXN];

int DFS(int v, int par){
    int subtree_sz, sz = 1, blocked = 0;
    in[v] = low[v] = timer++;
    ans[v] = 2LL * (n - 1);
    for (int child : adj[v]){
        if (in[child] == -1){
            subtree_sz = DFS(child, v);
            sz += subtree_sz;
            if (low[child] >= in[v]){
                ans[v] += (lli) (n - subtree_sz - 1) * subtree_sz; 
                blocked += subtree_sz; 
            }
            else {
                low[v] = min(low[v], low[child]);
            }
        }
        else if (child != par){
            low[v] = min(low[v], in[child]);
        }
    }
    ans[v] += (lli) (n - blocked - 1) * blocked;
    return sz;
}

void solve(){
	int m, a, b;
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    memset(in, -1, sizeof(in));
    DFS(1, -1);
    for (int i = 1; i <= n; i++){
        cout << ans[i] << "\n";
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
