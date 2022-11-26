//XXII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 5e4 + 3, SQRT = 227, LOG = 16;

vector <int> adj[MAXN];
int cost[MAXN], trip[MAXN], depth[MAXN], up[MAXN][LOG], pref[MAXN][SQRT]; // pref[v][k] = koszt przejścia 1-v, jeżeli zaliczamy co k-ty

int LCA(int u, int v){
    if (depth[u] < depth[v]){
        swap(u, v);
    }
    int d = depth[u] - depth[v];
    for (int b = 0; b < LOG; b++){
        if (d & (1 << b)){
            u = up[u][b];
        }
    }
    if (u == v){
        return u;
    }
    for (int b = LOG - 1; b >= 0; b--){
        if (up[u][b] != up[v][b]){
            u = up[u][b];
            v = up[v][b];
        }
    }
    return up[u][0];
}

int kth(int v, int k){
    for (int b = 0; b < LOG; b++){
        if (k & (1 << b)){
            v = up[v][b];   
        }
    }
    return v;
}

void DFS_LCA(int v, int par, int dep){
	up[v][0] = par;
    depth[v] = dep;
	for (int child : adj[v]){
        if (child != par){
            DFS_LCA(child, v, dep + 1);
        }
    }
}

void DFS(int v, int par){    
    int u;
    for (int i = 1; i < SQRT; i++){
        pref[v][i] = cost[v];
        u = kth(v, i);
        if (u != 0){
            pref[v][i] += pref[u][i]; 
        }
    }
	for (int child : adj[v]){
        if (child != par){
            DFS(child, v);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int n, k, a, b;
	cin >> n;
	for (int i = 1; i <= n; i++){
	    cin >> cost[i];
	}
	for (int i = 0; i < n - 1; i++){
	    cin >> a >> b;
	    adj[a].push_back(b);
	    adj[b].push_back(a);
	}
	
	DFS_LCA(1, 0, 0);
	for (int b = 1; b < LOG; b++){
	    for (int i = 1; i <= n; i++){
	        up[i][b] = up[up[i][b - 1]][b - 1];
	    }
	}
	DFS(1, 0);
	
	for (int i = 0; i < n; i++){
	    cin >> trip[i];
	}
	
	int l, ll, d1, d2, len, u, v, ans;
	for (int i = 0; i < n - 1; i++){
	    cin >> k;
	    u = trip[i];
	    v = trip[i + 1];
	    l = LCA(u, v), d1 = depth[u] - depth[l], d2 = depth[v] - depth[l];
	    
	    if (k >= SQRT){
    	    ans = cost[u] + cost[v];
    	    len = 0;
    	    while (len + k <= d1){
    	        len += k;
    	        u = kth(u, k);
    	        ans += cost[u];
    	    }
    	    len = 0;
    	    while (len + k <= d2){
    	        len += k;
    	        v = kth(v, k);
    	        ans += cost[v];
    	    }
    	    if (u == v){
    	        ans -= cost[v];
    	    }
	    }
	    else{
	        ans = pref[u][k] + pref[v][k];
			if ((depth[l] - depth[u]) % k == 0){
				ans -= 2 * pref[l][k];
				ans += cost[l];
			}
			else{
				ll = l;
				while ((depth[l] - depth[u]) % k != 0 && l != up[l][0]){
					l = up[l][0];
				}
				ans -= pref[l][k];
				l = ll;
				while ((depth[l] - depth[v]) % k != 0 && l != up[l][0]){
					l = up[l][0];
				}
				ans -= pref[l][k];
			}
	    }
	    cout << ans << "\n";
	}
    return 0;
}
