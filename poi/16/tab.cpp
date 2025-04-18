#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e6 + 3, P = 2'000'029, MOD = 777'777'799;

lli p[MAXN];

lli madd(lli a, lli b){
    return (a + b) % MOD;
}

lli mmul(lli a, lli b){
    return (a * b) % MOD;
}

void solve(){
    int n, m;
    cin >> n >> m;
    bool ok = true;
    vector <vector <lli>> a(n, vector <lli>(m));
    vector <lli> b(m);
    map <lli, int> mp_r, mp_c;
    lli h;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> a[i][j];
            a[i][j] += MAXN; // to avoid negatives
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            b[j] = a[i][j]; 
        }
        sort(b.begin(), b.end());

        h = 0;
        for (int j = 0; j < m; j++){
            h = madd(h, mmul(b[j], p[j]));
        }
        mp_r[h]++;
    }
    b.resize(n);
    for (int j = 0; j < m; j++){
        for (int i = 0; i < n; i++){
            b[i] = a[i][j]; 
        }
        sort(b.begin(), b.end());

        h = 0;
        for (int i = 0; i < n; i++){
            h = madd(h, mmul(b[i], p[i]));
        }
        mp_c[h]++;
    }
    b.resize(m);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> a[i][j];
            a[i][j] += MAXN;
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            b[j] = a[i][j]; 
        }
        sort(b.begin(), b.end());

        h = 0;
        for (int j = 0; j < m; j++){
            h = madd(h, mmul(b[j], p[j]));
        }
        if (mp_r[h] == 0){
            ok = false;
        }
        else{
            mp_r[h]--;
        }
    }
    b.resize(n);
    for (int j = 0; j < m; j++){
        for (int i = 0; i < n; i++){
            b[i] = a[i][j]; 
        }
        sort(b.begin(), b.end());

        h = 0;
        for (int i = 0; i < n; i++){
            h = madd(h, mmul(b[i], p[i]));
        }
        if (mp_c[h] == 0){
            ok = false;
        }
        else{
            mp_c[h]--;
        }
    }
    b.resize(m);

    cout << (ok ? "TAK\n" : "NIE\n");
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    p[0] = 1;
    for (int i = 1; i < MAXN; i++){
        p[i] = mmul(p[i - 1], P);
    }

    int t = 1;
    cin >> t;
    while (t--){
        solve();
    }
    return 0;
}   
