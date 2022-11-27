//XXIX OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int maxfib = 89;

lli fib[maxfib + 1];

void gen_fib(){
    fib[1] = 1;
    fib[2] = 1;
    for (int i = 3; i <= maxfib; i++){
        fib[i] = fib[i - 1] + fib[i - 2];
    }
}

void solve(){
    gen_fib();
    lli n;
    cin >> n;

    if (n == 1){
        cout << "1\n";
        return;
    }

    for (int i = maxfib; i >= 3; i--){
        if (fib[i] == n){
            cout << i - 1 << "\n";
            return;
        }
    }

    int sum_ind = 0, bar = 0, ile_2 = 0, ile_3 = 0, cnt = 0;

    for (int i = maxfib; i >= 3; i--){
        if (fib[i] > n || fib[i] == 144 || fib[i] == 8){
            continue;
        }
        cnt = 0;
        while (n % fib[i] == 0){
            n /= fib[i];
            if (fib[i] != 2 && fib[i] != 3){
                sum_ind += i - 1;
                bar++;
            }
            cnt++;
        }
        
        if (fib[i] == 3){
            ile_3 = cnt;
        }
        if (fib[i] == 2){
            ile_2 = cnt;
        }
    }

    if (n != 1){
        cout << "NIE\n";
        return;
    }

    int ile_144 = min(ile_2 / 4, ile_3 / 2);
    ile_2 -= ile_144 * 4;
    ile_3 -= ile_144 * 2;

    sum_ind += ile_144 * 11;
    bar += ile_144;

    int ile_8 = ile_2 / 3;
    ile_2 -= ile_8 * 3;

    sum_ind += ile_8 * 5;
    bar += ile_8;

    sum_ind += ile_3 * 3 + ile_2 * 2;
    bar += ile_3 + ile_2;

    cout << sum_ind + bar - 1 << "\n";

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
