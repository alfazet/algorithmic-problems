#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const int MAXN = 2e5 + 3, MAXM = 4e5 + 3;

pair <int, int> hold[MAXN], hold_cp[MAXN], events[MAXM]; // event = {monkey, paw}

struct DSU{
    int n;
    vector <int> par, ans;
    vector <vector <int>> members;

    void init(int n_){
        n = n_;
        par.resize(n + 1);
        iota(par.begin(), par.end(), 0);
        members.resize(n + 1);
        for (int i = 1; i <= n; i++){
            members[i].push_back(i);
        }
        ans.assign(n + 1, -1);
    }

    int find(int x){
        if (x == par[x]){
            return x;
        }
        return par[x] = find(par[x]);
    }

    void merge(int u, int v, int t){
        u = find(u);
        v = find(v);
        if (u == v){
            return;
        }
        if (members[u].size() > members[v].size()){
            swap(u, v);
        }
        if (u == find(1)){
            for (int x : members[v]){
                ans[x] = t;
            }
        }
        if (v == find(1)){
            for (int x : members[u]){
                ans[x] = t;
            }
        }
        while (!members[u].empty()){
            int x = members[u].back();
            members[u].pop_back();
            members[v].push_back(x);
            par[x] = v;
        }
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, v, paw;
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        cin >> hold[i].ff >> hold[i].ss;
        hold_cp[i] = hold[i];
    }
    for (int i = 0; i < m; i++){ // saving events to "play them back"
        cin >> v >> paw;
        if (paw == 1){
            hold[v].ff = -1;
        }
        else{
            hold[v].ss = -1;
        }
        events[i] = {v, paw};
    }

    DSU ds;
    ds.init(n);
    for (int i = 1; i <= n; i++){ // building the ending state
        if (hold[i].ff != -1){
            ds.merge(i, hold[i].ff, -1);
        }
        if (hold[i].ss != -1){
            ds.merge(i, hold[i].ss, -1);
        }
    }

    for (int i = m - 1; i >= 0; i--){ // playback
        if (events[i].ss == 1){
            ds.merge(events[i].ff, hold_cp[events[i].ff].ff, i);
        }
        else{
            ds.merge(events[i].ff, hold_cp[events[i].ff].ss, i);
        }
    }
    for (int i = 1; i <= n; i++){
        cout << ds.ans[i] << "\n";
    }

    return 0;
}
