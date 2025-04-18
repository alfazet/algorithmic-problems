#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

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
        if (sz[u] > sz[v]){
            swap(u, v);
        }
        par[u] = v;
        sz[v] += sz[u];
        return true;
    }
};

int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n;
    int ccs = n;
    DSU ds;
    ds.init(n);
    for (int i = 1; i <= n; i++){
        cin >> x;
        ccs -= ds.merge(i, x);
    }
    cout << ccs << "\n";

    return 0;
}   
