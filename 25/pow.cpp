#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MOD = 1e9 + 7;

lli madd(lli a, lli b){
    return (a + b) % MOD;
}

lli msub(lli a, lli b){
    return ((a - b) % MOD + MOD) % MOD;
}

lli mmul(lli a, lli b){
    return (a * b) % MOD;
}

struct Dam{
    int u, v;
    lli d; // {cell 1, cell 2, height}

    Dam(int u_ = 0, int v_ = 0, lli d_ = 0) : u(u_), v(v_), d(d_) {};

    bool operator < (Dam other){
        return d < other.d;
    }
};

struct DSU{
    int n;
    vector <int> par, sz, water_height;
    vector <lli> ways;

    void init(int n_){
        n = n_;
        par.resize(n + 1);
        sz.resize(n + 1);
        ways.resize(n + 1);
        water_height.resize(n + 1);
        for (int i = 1; i <= n; i++){
            par[i] = i;
            sz[i] = ways[i] = 1;
        }
    }

    int find(int x){
        if (x == par[x]){
            return x;
        }
        return par[x] = find(par[x]);
    }

    void merge(int u, int v, lli h){
        u = find(u);
        v = find(v);
        if (u == v){
            return;
        }
        if (sz[u] > sz[v]){
            swap(u, v);
        }
        par[u] = v;
        sz[v] += sz[u];
        ways[v] = mmul(madd(ways[v], msub(h, water_height[v])), madd(ways[u], msub(h, water_height[u])));
        water_height[v] = h;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int h, w, max_d, d;
    cin >> h >> w >> max_d;
    vector <Dam> dams;
    for (int i = 0; i < h; i++){
        for (int j = 1; j <= w - 1; j++){
            cin >> d;
            dams.emplace_back(w * i + j, w * i + j + 1, d);
        }
    }
    for (int i = 0; i < h - 1; i++){
        for (int j = 1; j <= w; j++){
            cin >> d;
            dams.emplace_back(w * i + j, w * (i + 1) + j, d);
        }
    }

    sort(dams.begin(), dams.end());
    DSU ds; ds.init(h * w);
    for (auto[u, v, d] : dams){
        ds.merge(u, v, d);
    }
    int all = ds.find(1);
    cout << madd(ds.ways[all], msub(max_d, ds.water_height[all])) << "\n";

    return 0;
}   
