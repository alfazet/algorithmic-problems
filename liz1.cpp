//XVIII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int maxn = 2e6 + 2;

int dpL[maxn], dpR[maxn];
int type[maxn / 2];

void memo(int l, int r, int sum){
    dpL[sum] = l;
    dpR[sum] = r;
    if (sum >= 3){
        if (type[l] == 2){
            memo(l + 1, r, sum - 2);
        }
        else if (type[r] == 2){
            memo(l, r - 1, sum - 2);
        }
        else{
            memo(l + 1, r - 1, sum - 2);
        }
    }
}

void solve(){
    int n, m, suma = 0, k;
    char c;
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        cin >> c;
        if (c == 'T'){
            type[i] = 2;
            suma += 2;
        }
        else{
            type[i] = 1;
            suma += 1;
        }
    }
    memo(1, n, suma);
    int l = -1, r = -1;
    for (int i = 1; i <= n; i++){
        if (type[i] == 1){
            l = i;
            break;
        }
    }
    for (int i = n; i >= 1; i--){
        if (type[i] == 1){
            r = i;
            break;
        }
    }
    if (l - 1 < n - r && l != -1){
        memo(l + 1, n, suma - 2 * (l - 1) - 1);
    }
    else if (r != -1){
        memo(1, r - 1, suma - 2 * (n - r) - 1);
    }
    while (m--){
        cin >> k;
        if (dpL[k] == 0 || dpR[k] == 0){
            cout << "NIE\n";
        }
        else{
            cout << dpL[k] << " " << dpR[k] << "\n";
        }
    }
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
