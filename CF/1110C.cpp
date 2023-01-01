#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

void solve(){
	int n;
    cin >> n;
    int next_pow_2 = 1;
    while (next_pow_2 <= n || __builtin_popcount(next_pow_2) != 1){
        next_pow_2 *= 2;
    }
    if (next_pow_2 == n + 1){ // n = 11..11, so n ^ x = n - x and n ^ x = x, and since gcd(a, b) = gcd(a - b, b) we can set x to the biggest proper divisor
        for (int i = 2; i * i <= n; i++){
            if (n % i == 0){
                cout << n / i << "\n";
                return;
            }
        }
        cout << "1\n";
    }
    else{
        cout << next_pow_2 - 1 << "\n"; // b = a with inverted bits, then gcd(a ^ b, a & b) = gcd(2^k - 1, 0) = 2^k - 1
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    cin >> t;
    while (t--){
        solve();
    }
    return 0;
}   
