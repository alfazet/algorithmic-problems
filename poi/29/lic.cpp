#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    lli n, k;
    int c;
    cin >> n >> k >> c;

    auto factorize = [&](lli x){
        vector <lli> f;
        for (lli i = 2; i * i <= x; i++){
            if (x % i == 0){
                f.push_back(i);
                while (x % i == 0){
                    x /= i;
                }
            }
        }
        if (x > 1){
            f.push_back(x);
        }
        return f;
    };

    vector <lli> f = factorize(n);
    auto count = [&](lli x){ // how many coprime numbers up to x 
        int cnt = f.size();
        lli ans = 0, q;
        for (int mask = 0; mask <= (1 << cnt) - 1; mask++){
            q = 1;
            for (int b = 0; b < cnt; b++){
                if (mask & (1 << b)){
                    q *= f[b];
                }
            }
            if (__builtin_popcount(mask) % 2 == 0){
                ans += x / q;
            }
            else{
                ans -= x / q;
            }
        }
        return ans;
    };

    // we want the smallest number x s.t. count(x) == k
    lli x = (1LL << 60) - 1;
    for (int b = 60; b >= 0; b--){
        x -= (1LL << b);
        if (count(x) < k){
            x += (1LL << b);
        }
    }
    while (c){ // phi(n) / n < 8n so this is quite fast
        if (gcd(x, n) == 1){
            cout << x << " ";
            c--;
        }
        x++;
    }
    cout << "\n";

    return 0;
}   
