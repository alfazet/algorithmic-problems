//IOI 2011
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1.5e5 + 11, INF = 1e9 + 7;

// v = weszliśmy do v nie najlepszą lub wystrtowaliśmy
// v' = weszliśmy najlepszą

int X, cycle_len_1 = INF, cycle_len_2 = INF;
int in[MAXN], nxt[2 * MAXN], dist[2 * MAXN][2]; // dist[v][0/1] - odległość od X/X' do v
vector <int> adj[2 * MAXN];
// nxt[v + MAXN] = nxt[v']

bool vis[2 * MAXN][2];

string print_v(int v){ // utility, wypisuje v' zamiast śmieci
    string s;
    if (v > MAXN){
        return to_string(v - MAXN) + "'";
    }
    return to_string(v);
}

void DFS(int v, const int &typ, int d){
    vis[v][typ] = true;
    dist[v][typ] = d;
    for (int child : adj[v]){
        if (!vis[child][typ]){
            DFS(child, typ, d + 1);
        }
        if (typ == 0 && child == X){
            cycle_len_1 = d + 1;
            continue;
        }
        if (typ == 1 && child == X + MAXN){
            cycle_len_2 = d + 1;
            continue;
        }
    }
}

void solve(){
    int n, m, a, b;
    cin >> n >> m >> X;
    X++;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        a++;
        b++;

        if (in[a] == 0){ // wchodzimy najlepszą do a
            if (in[b] == 0){ // i jest to najlepsza krawędź incydentna z b
                nxt[b] = a + MAXN;
            }
            else{ // nie najlepsza incydentna z b
                if (nxt[b + MAXN] == 0){
                    nxt[b + MAXN] = a + MAXN;
                }
            }
        }
        else{ // wchodzimy nie najlepszą do a
            if (in[b] == 0){ // i jest to najlepsza krawędź incydentna z b
                nxt[b] = a;
            }
            else{ // nie najlepsza incydentna z b
                if (nxt[b + MAXN] == 0){
                    nxt[b + MAXN] = a;
                }
            }
        }

        if (in[b] == 0){ // wchodzimy najlepszą do b
            if (in[a] == 0){ // i jest to najlepsza krawędź incydentna z a
                nxt[a] = b + MAXN;
            }
            else{ // nie najlepsza incydentna z a
                if (nxt[a + MAXN] == 0){
                    nxt[a + MAXN] = b + MAXN;
                }
            }
        }
        else{ // wchodzimy nie najlepszą do b
            if (in[a] == 0){ // i jest to najlepsza krawędź incydentna z a
                nxt[a] = b;
            }
            else{ // nie najlepsza incydentna z a
                if (nxt[a + MAXN] == 0){
                    nxt[a + MAXN] = b;
                }
            }
        }
        in[a]++;
        in[b]++;
    }

    for (int i = 1; i <= n; i++){
        if (in[i] == 1){
            if (nxt[i] != 0){
                nxt[i + MAXN] = nxt[i];
            }
            else{
                nxt[i] = nxt[i + MAXN];
            }
        }
        adj[nxt[i]].push_back(i);
        adj[nxt[i + MAXN]].push_back(i + MAXN);
        dist[i][0] = INF;
        dist[i + MAXN][0] = INF;
        dist[i][1] = INF;
        dist[i + MAXN][1] = INF;
    }


    DFS(X, 0, 0); // DFS "od tylu" od X
    DFS(X + MAXN, 1, 0);

    int Q, ans, k;
    cin >> Q;
    while (Q--){
        ans = 0;
        cin >> k;
        for (int i = 1; i <= n; i++){
            if (dist[i][0] == k || (dist[i][0] != INF && cycle_len_1 != INF && k > dist[i][0] && (k - dist[i][0]) % cycle_len_1 == 0)){
                ans++;
            }
            if (dist[i][1] == k || (dist[i][1] != INF && cycle_len_2 != INF && k > dist[i][1] && (k - dist[i][1]) % cycle_len_2 == 0)){
                ans++;
            }
        }
        cout << ans << " ";
    }
    cout << "\n";
}

int main (){
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
