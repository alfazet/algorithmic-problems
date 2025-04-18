#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int P[2] = {79, 97}, MOD[2] = {777'777'799, 999'999'797};

lli madd(lli a, lli b, int q){
    return (a + b) % MOD[q];
}

lli msub(lli a, lli b, int q){
    return ((a - b) % MOD[q] + MOD[q]) % MOD[q];
}

lli mmul(lli a, lli b, int q){
    return (a * b) % MOD[q];
}

lli ord(char c){
    return (lli) (c - 'a') + 1;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int n = s.size();
    vector <bool> ok(27);
    char c;
    for (int i = 1; i <= 26; i++){
        cin >> c;
        ok[i] = (c == '1');
    }
    int k;
    cin >> k;

    vector <vector <lli>> p(n, vector <lli>(2));
    p[0][0] = p[0][1] = 1;
    for (int i = 1; i < n; i++){
        for (int r = 0; r < 2; r++){
            p[i][r] = mmul(p[i - 1][r], P[r], r);
        }
    }

    vector <vector <lli>> h(n, vector <lli>(2));
    for (int i = 0; i < n; i++){
        for (int r = 0; r < 2; r++){
            h[i][r] = madd(i == 0 ? 0 : h[i - 1][r], mmul(ord(s[i]), p[i][r], r), r);
        }
    }

    auto get_substr_hash = [&](int l, int r, int q){
        return mmul(msub(h[r][q], (l == 0 ? 0 : h[l - 1][q]), q), p[n - l - 1][q], q);
    };

    set <pair <lli, lli>> ans;
    int bad;
    for (int i = 0; i < n; i++){
        bad = 0;
        for (int j = i; j < n; j++){
            if (!ok[ord(s[j])]){
                bad++;
            }

            if (bad > k){
                break;
            }
            ans.insert(make_pair(get_substr_hash(i, j, 0), get_substr_hash(i, j, 1)));
        }
    }
    cout << ans.size() << "\n";

    return 0;
}
