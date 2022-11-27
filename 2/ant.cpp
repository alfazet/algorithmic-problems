//VIII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

lli n;
lli primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
vector <pair <lli, lli>> antiprimes;

void generator(lli prime_id, lli pow, lli p, lli num_divs){
    antiprimes.push_back({p, num_divs});
    for (int i = 1; i <= pow; i++){
        if (p * primes[prime_id] <= n){
            p *= primes[prime_id];
            generator(prime_id + 1, i, p, num_divs * (i + 1));
        }
        else{
            return;
        }
    }
}

void solve(){
    cin >> n;
    generator(0, 32, 1, 1);
    sort(antiprimes.begin(), antiprimes.end());
    lli best = 1, most_divs = 1;
    for (auto p : antiprimes){
        if (p.second > most_divs){
            best = p.first;
            most_divs = p.second;
        }
    }
    cout << best << "\n";
}

int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    t = 1;
    //cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
