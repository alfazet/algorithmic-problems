//VII OI 
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int maxn = 1e4 + 3;

lli z[maxn], d[maxn];
lli ans = 1e17, cost;
lli dl, dr, zl, zr, l = 2, r = 1, D;
int n;

void fix(){
    while (d[r] + dr < dl){
        cost += z[l] * (d[r] + dr) - z[l] * dl;
        dl -= d[l];
        dr += d[r];
        zl -= z[l];
        zr += z[l];

        l = (l % n) + 1;
        r = (r % n) + 1;
    }
}

void solve(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> z[i] >> d[i];
    }
    for (int i = n; i >= 2; i--){
        dl += d[i];
        zl += z[i];
        cost += dl * z[i];
    }
    fix();
    ans = cost;
    for (int i = 2; i <= n; i++){
        D = d[i - 1];
        cost += D * (zl + z[i - 1]) - D * zr;
        dl += D;
        dr -= D;
        zl += z[i - 1];
        zr -= z[i];
        fix();
        ans = min(cost, ans);
    }
    cout << ans << "\n";
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
