//V OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e3 + 3;

int ktory_v[MAXN][MAXN], cnt_edge[MAXN][MAXN], dp[MAXN][2], h[MAXN];
vector <int> adj[MAXN];

// max. poddrzewo, w którym są max. 3 liście
void DFS(int v, int par){
    vector <int> ch;
    for (int child : adj[v]){
        if (child != par){
            DFS(child, v);
            ch.push_back(child);
        }
    }
    if ((int) ch.size() == 1){
        h[v] = h[ch[0]] + 1;
        dp[v][0] = dp[ch[0]][0] + 1;
        dp[v][1] = dp[ch[0]][1];
    }
    else if ((int) ch.size() == 2){
        h[v] = max(h[ch[0]], h[ch[1]]) + 1;
        dp[v][0] = h[ch[0]] + h[ch[1]] + 1;
        dp[v][1] = max({dp[ch[0]][1], dp[ch[1]][1], h[ch[0]] + dp[ch[1]][0] + 1, dp[ch[0]][0] + h[ch[1]] + 1});
    }
    else if ((int) ch.size() == 3){
        dp[v][1] = max({dp[ch[0]][1], dp[ch[1]][1], dp[ch[2]][1], 
        dp[ch[0]][0] + max(h[ch[1]], h[ch[2]]) + 1, dp[ch[1]][0] + max(h[ch[0]], h[ch[2]]) + 1, dp[ch[2]][0] + max(h[ch[0]], h[ch[1]]) + 1,
        h[ch[0]] + h[ch[1]] + h[ch[2]] + 1});
    }
    else{
        h[v] = 1;
    }
}

void solve(){
    int n;
    cin >> n;
    int a[3];
    for (int i = 1; i <= n - 2; i++){
        cin >> a[0] >> a[1] >> a[2];
        a[0]++;
        a[1]++;
        a[2]++;
        sort(a, a + 3);
        cnt_edge[a[0]][a[1]]++;
        if (cnt_edge[a[0]][a[1]] == 2){
            adj[i].push_back(ktory_v[a[0]][a[1]]);
            adj[ktory_v[a[0]][a[1]]].push_back(i);
        }
        cnt_edge[a[0]][a[2]]++;
        if (cnt_edge[a[0]][a[2]] == 2){
            adj[i].push_back(ktory_v[a[0]][a[2]]);
            adj[ktory_v[a[0]][a[2]]].push_back(i);
        }
        cnt_edge[a[1]][a[2]]++;
        if (cnt_edge[a[1]][a[2]] == 2){
            adj[i].push_back(ktory_v[a[1]][a[2]]);
            adj[ktory_v[a[1]][a[2]]].push_back(i);
        }
        ktory_v[a[0]][a[1]] = ktory_v[a[0]][a[2]] = ktory_v[a[1]][a[2]] = i;
    }
    if (n == 3){
        cout << "1\n";
        return;
    }
    int mx_deg = 0, cnt_deg_1 = 0, root = 0;
    for (int i = 1; i <= n - 2; i++){
        if ((int) adj[i].size() > mx_deg){
            mx_deg = adj[i].size();
            root = i;
        }
        if (adj[i].size() == 1){
            cnt_deg_1++;
        }
    }
    if (mx_deg <= 2){
        cout << n - 2 << "\n";
        return;
    }
    DFS(root, -1);
    cout << dp[root][1] << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    //cin >> t;
    while (t--){
        solve();
    }
    return 0;
}   
