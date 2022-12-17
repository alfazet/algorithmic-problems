#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, X, x, a, b, prev_x = 0, low, high;
    cin >> n >> X;
    lli ans = 0;
    if (n == 0){
        cout << "0\n";
        return 0;
    }
    pair <int, int> range = {0, 0};
    for (int i = 0; i < n; i++){
        cin >> x >> a >> b;
        low = max(a + 1, range.ff - (x - prev_x));
        high = min(b - 1, range.ss + (x - prev_x));
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
            return 0;
        }
        range.ff = low;
        range.ss = high;
        prev_x = x;
    }
    int min_ending_height = low - X + prev_x;
    cout << (X + min_ending_height) / 2 << "\n";

    return 0;
}
