#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e8;

bitset <MAXN + 1> prime;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    for (int i = 2; i <= MAXN; i++){
        prime[i] = true;
    }
    for (int i = 2; i * i <= MAXN; i++){
        if (prime[i]){
            for (int j = i * i; j <= MAXN; j += i){
                prime[j] = false;
            }
        }
    }
    vector <int> p;
    for (int i = 2; i <= MAXN; i++){
        if (prime[i]) p.push_back(i);
    }

    lli n;
    cin >> n;
    int sz = p.size(), l = 0, r = 0;
    lli sum = 0;
    while (r < sz){
        sum += p[r];
        while (l < r && sum > n){
            sum -= p[l];
            l++;
        } 
        if (sum == n){
            cout << p[l] << " " << p[r] << "\n";
            return 0;
        }
        r++;
    }
    
    if (n <= MAXN){ // if a number is <= 10^8 and it we can't make it using numbers <= 10^8, then we can't make it for sure
        cout << "NIE\n";
        return 0;
    }

    auto seg_sieve = [&](lli l, lli r){
        lli root = (lli) sqrt(r) + 10;

        vector <lli> primes_up_to_sqrt;
        for (lli i = 2; i <= root; i++){
            if (prime[i]){
                primes_up_to_sqrt.push_back(i);
            }
        }

        vector <bool> prime_segement(r - l + 1, true);
        for (lli i : primes_up_to_sqrt){
            for (lli j = max(i * i, (l + i - 1) / i * i); j <= r; j += i){
                prime_segement[j - l] = false;
            }
        }

        vector <lli> primes_in_l_r;
        for (int i = 0; i < r - l + 1; i++){
            if (prime_segement[i]){
                primes_in_l_r.push_back(i + l);
            }
        }
        return primes_in_l_r;
    };

    int d;
    lli m;
    vector <lli> big_p_left, big_p_right, big_p;
    for (int k = 1; k <= 1000; k++){ // 1000 seems to be enough since we need at most ~1000 numbers of size ~10^8 to sum up to 10^11 
        m = n / k; // middle

        // left side
        d = k;
        do{
            big_p_left = seg_sieve(m - d, m);
            d *= 2;
        } while ((int) big_p_left.size() < k);

        // right side
        d = k;
        do{
            big_p_right = seg_sieve(m + 1, m + d);
            d *= 2;
        } while ((int) big_p_right.size() < k);

        big_p.clear();
        for (lli x : big_p_left){
            big_p.push_back(x);
        }
        for (lli x : big_p_right){
            big_p.push_back(x);
        }

        sz = big_p.size(), l = 0, r = 0;
        sum = 0;
        while (r < sz){
            sum += big_p[r];
            while (l < r && sum > n){
                sum -= big_p[l];
                l++;
            } 
            if (sum == n){
                cout << big_p[l] << " " << big_p[r] << "\n";
                return 0;
            }
            r++;
        }
    }
    cout << "NIE\n";

    return 0;
}   
