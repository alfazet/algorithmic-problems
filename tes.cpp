#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e6 + 3;

vector <int> occs[MAXN];

bool check(const vector <int> &a){
    int last_used = -1, where;
    for (int x : a){
        if (occs[x].empty()){
            return false;
        }
        auto it = upper_bound(occs[x].begin(), occs[x].end(), last_used);
        if (it - occs[x].begin() == (int) occs[x].size()){
            return false;
        }
        where = *it;
        if (where <= last_used){
            return false;
        }
        last_used = where;
    }
    return true;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x, q, m;
    cin >> n;
    vector <int> a;
    for (int i = 0; i < n; i++){
        cin >> x;
        occs[x].push_back(i);
    }
    cin >> q;
    while (q--){
        cin >> m;
        a.resize(m);
        for (int i = 0; i < m; i++){
            cin >> a[i];
        }
        cout << (check(a) ? "TAK\n" : "NIE\n");
    }

    return 0;
}
