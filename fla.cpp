//XXIV OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

void solve(){
    int n, X, x, a, b, prev_x = 0, low, high;
    cin >> n >> X;
    lli ans = 0;
    if (n == 0){
        cout << "0\n";
        return;
    }
    pair <int, int> range = make_pair(0, 0); //low, high
    for (int i = 0; i < n; i++){
        cin >> x >> a >> b;
        low = max(a + 1, range.first - (x - prev_x));
        high = min(b - 1, range.second + (x - prev_x));
        if (x % 2 == 0){
            if (low % 2 != 0){
                low++;
            }
            if (high % 2 != 0){
                high--;
            }
        }
        else{
            if (low % 2 == 0){
                low++;
            }
            if (high % 2 == 0){
                high--;
            }
        }
        if (low > high){
            cout << "NIE\n";
            return;
        }
        range.first = low;
        range.second = high;
        prev_x = x;
    }
    int min_ending_height = low - X + prev_x;
    cout << (X + min_ending_height) / 2 << "\n";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int t;
    //cin >> t;
    t = 1;
    while (t--){
        solve();
    }
    return 0;
}
