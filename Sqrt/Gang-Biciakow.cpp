//XXVIII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const int MAXN = 1e5 + 3, MAXM = 1.5e5 + 3, SQRT = 333;

vector <pair <int, int>> adj[MAXN];
pair <int, int> edges[MAXN];
vector <int> big[SQRT + 2];
int biciak[MAXN], big_id[MAXN], normal_id[MAXN], parent[MAXN], edge_to_parent[MAXN], ile[SQRT + 2], in[MAXN], out[MAXN], timer, cnt_big;

//big[v] - wektor częstości biciaków na sciezce do korzenia z wierzcholka o duzym indeksie v 

int DFS_precomp(int v, int par, int depth, vector <int> &freq, int rozne, int edge_id){
    in[v] = timer++;
    parent[v] = par;
    edge_to_parent[v] = edge_id;
    bool flag = false;
    int max_path = 0;
    for (auto child : adj[v]){
        if (child.ff != par){
            freq[biciak[child.ss]]++;
            if (freq[biciak[child.ss]] == 1){
                flag = true;
            }
            max_path = max(max_path, DFS_precomp(child.ff, v, depth + 1, freq, rozne + flag, child.ss) + 1);
            freq[biciak[child.ss]]--;
        }
    }
    out[v] = timer++;
    if (depth % SQRT == 0 && max_path >= SQRT){
        big_id[v] = ++cnt_big;
        normal_id[cnt_big] = v;
        big[big_id[v]] = freq;
        ile[big_id[v]] = rozne;
    }
    return max_path;
}

int query(int v){
    unordered_set <int> seen;
    while (parent[v] != -1 && big_id[v] == 0){
        seen.insert(biciak[edge_to_parent[v]]);
        v = parent[v];
    }
    if (parent[v] == -1){
        return seen.size();
    }
    int ans = 0;
    for (int b : seen){
        if (big[big_id[v]][b] == 0){
            ans++;
        }
    }
    return ans + ile[big_id[v]];
}

void update(int id, int nowy){
    int so_far = biciak[id], u = edges[id].ff, v = edges[id].ss, w;
    biciak[id] = nowy;
    if (parent[v] == u){ 
        swap(u, v);
    }
    for (int i = 1; i <= cnt_big; i++){
        w = normal_id[i];
        if (in[w] >= in[u] && out[w] <= out[u]){
            big[i][so_far]--;
            if (big[i][so_far] == 0){
                ile[i]--;
            }
            big[i][nowy]++;
            if (big[i][nowy] == 1){
                ile[i]++;
            }
        }
    }
}

void solve(){
	int n, m, q, a, b, c, v, id, x;
    char ch;
    cin >> n >> m >> q;
    for (int i = 1; i <= n - 1; i++){
        cin >> a >> b >> c;
        adj[a].emplace_back(b, i);
        adj[b].emplace_back(a, i);
        biciak[i] = c;
        edges[i] = {a, b};
    }
    vector <int> freq(m + 1);
    DFS_precomp(1, -1, 0, freq, 0, -1);
    while (q--){
        cin >> ch;
        if (ch == 'Z'){
            //ile rodzajow na sciezce do v
            cin >> v;
            cout << query(v) << "\n";
        }
        else{
            //na i-tej drodze teraz jest biciak x
            cin >> id >> x;
            update(id, x);
        }
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
