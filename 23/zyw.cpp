#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 2e6 + 3;

struct DSU{
    int n;
    vector <int> par, sz;

    void init(int n_){
        n = n_;
        par.resize(n + 1);
        sz.resize(n + 1);
        for (int i = 1; i <= n; i++){
            par[i] = i;
            sz[i] = 1;
        }
    }

    int find(int x){
        if (x == par[x]){
            return x;
        }
        return par[x] = find(par[x]);
    }

    bool merge(int u, int v){
        u = find(u);
        v = find(v);
        if (u == v){
            return false;
        }
        if (sz[v] < sz[u]){
            swap(u, v);
        }
        par[u] = v;
        sz[v] += sz[u];
        return true;
    }
};

struct Edge{
    int u, v, w, id_r, id_c, id_where;

    Edge(int u_, int v_, int w_, int id_r_, int id_c_, int id_where_) : u(u_), v(v_), w(w_), id_r(id_r_), id_c(id_c_), id_where(id_where_) {};

    bool operator < (Edge &e){
        return w < e.w;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int n, m;
    cin >> m >> n;
    int sz = (n + 1) * (m + 1);
    DSU ds; ds.init(sz);

    // fence
    for (int i = 1; i <= n; i++){
        if (i != (n + 1) / 2) ds.merge(i, i + 1);
    }
    for (int j = n + 1; j <= sz - (n + 1); j += n + 1){
        ds.merge(j, j + n + 1);
    }
    for (int i = m * (n + 1) + 1; i <= sz - 1; i++){
        ds.merge(i, i + 1);
    }
    for (int j = 1; j <= (m - 1) * (n + 1) + 1; j += n + 1){
        ds.merge(j, j + n + 1);
    }

    // hedge
    char c;
    vector <Edge> edges;
    for (int j = 0; j < m; j++){
        for (int i = 2; i <= n; i++){
            cin >> c;
            edges.emplace_back(j * (n + 1) + i, (j + 1) * (n + 1) + i, (int) (c == 'T'), j, i - 2, 1);
        }
    }
    for (int j = 1; j <= m - 1; j++){
        for (int i = 1; i <= n; i++){
            cin >> c;
            edges.emplace_back(j * (n + 1) + i, j * (n + 1) + i + 1, (int) (c == 'T'), j - 1, i - 1, 2);
        }
    }
    sort(edges.begin(), edges.end());

    int weight = 0, cnt = 0;
    vector <vector <char>> ans1(m, vector <char>(n - 1, '.')), ans2(m - 1, vector <char>(n, '.'));
    for (auto[u, v, w, r, c, where] : edges){
        if (ds.merge(u, v)){
            cnt++;
            weight += w;
            if (where == 1) ans1[r][c] = 'Z';
            else ans2[r][c] = 'Z';
        }
    }

    cout << cnt << " " << cnt - weight << "\n";
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n - 1; j++){
            cout << ans1[i][j];
        }
        cout << "\n";
    }
    for (int i = 0; i < m - 1; i++){
        for (int j = 0; j < n; j++){
            cout << ans2[i][j];
        }
        cout << "\n";
    }

    return 0;
}   
