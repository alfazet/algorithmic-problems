#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 2e5 + 3, MOD = 1e9 + 7;

multiset <int> powers[MAXN]; // powers[p] = multiset of powers for every prime p
map <int, int> power_of[MAXN]; // power_of[i][p] = exponent of p in a[i] 
int min_of[MAXN]; // min_of[p] = minimal exponent of p

vector <pair <int, int>> factorize(int n){
    vector <pair <int, int>> v;
    for (int i = 2; i * i <= n; i++){
        if (n % i == 0){
            v.emplace_back(i, 0);
            while (n % i == 0){
                v.back().second++;
                n /= i;
            }
        }
    }
    if (n != 1){
        v.emplace_back(n, 1);
    }
    return v;
}

lli mmul(lli a, lli b){
    return (a * b) % MOD;
}

lli mpow(lli a, int b){
    lli res = 1;
    while (b){
        if (b % 2 == 1){
            res = mmul(res, a);
        }
        a = mmul(a, a);
        b /= 2;
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q, x;
    lli ans = 1;
    cin >> n >> q;
    
    auto query = [&](int i, int x){
        vector <pair <int, int>> factors = factorize(x);
        for (auto[p, e] : factors){
            if (power_of[i].count(p)){
                powers[p].erase(powers[p].find(power_of[i][p]));
                power_of[i][p] += e;
            }
            else{
                power_of[i][p] = e;
            }
            powers[p].insert(power_of[i][p]);

            int old_min = min_of[p];
            min_of[p] = ((int) powers[p].size() == n ? *(powers[p].begin()) : 0);
            ans = mmul(ans, mpow(p, min_of[p] - old_min));
        }
    };

    for (int i = 0; i < n; i++){
        cin >> x;
        query(i, x);
    }

    int i;
    while (q--){
        cin >> i >> x;
        i--;
        query(i, x);
        cout << ans << "\n";
    }

    return 0;
}   
