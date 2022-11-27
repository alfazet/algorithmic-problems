//XVI OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const lli BASE = 1e9 + 9, MOD = 1e9 + 7;

void solve(){
    int n, m;
    lli h, q;
    cin >> n >> m;
    lli a[n][m];
    multiset <lli> hash_r;
    multiset <lli> hash_c;
    lli temp[max(n, m)];
    multiset <lli> :: iterator it;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }
    //hashing rows
    for (int i = 0; i < n; i++){
        h = 0;
        for (int j = 0; j < m; j++){
            temp[j] = a[i][j];
        }
        sort(temp, temp + m);
        for (int j = 0; j < m; j++){
            h = h * BASE + temp[j];
        }
        hash_r.insert(h);
    }
    //hashing columns
    for (int j = 0; j < m; j++){
        h = 0;
        for (int i = 0; i < n; i++){
            temp[i] = a[i][j];
        }
        sort(temp, temp + n);
        for (int i = 0; i < n; i++){
            h = h * BASE + temp[i];
        }
        hash_c.insert(h);
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }
    //de-hashing rows
    for (int i = 0; i < n; i++){
        h = 0;
        for (int j = 0; j < m; j++){
            temp[j] = a[i][j];
        }
        sort(temp, temp + m);
        for (int j = 0; j < m; j++){
            h = h * BASE + temp[j];
        }
        it = hash_r.find(h);
        if (it != hash_r.end()){
            hash_r.erase(it);
        }
    }
    //de-hashing columns
    for (int j = 0; j < m; j++){
        h = 0;
        for (int i = 0; i < n; i++){
            temp[i] = a[i][j];
        }
        sort(temp, temp + n);
        for (int i = 0; i < n; i++){
            h = h * BASE + temp[i];
        }
        it = hash_c.find(h);
        if (it != hash_c.end()){
            hash_c.erase(it);
        }
    }

    cout << (hash_c.empty() && hash_r.empty() ? "TAK\n" : "NIE\n");
}

int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    //t = 1;
    cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
