#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int p, q, n;
    cin >> p >> q >> n;
    if (p > q){
        swap(p, q);
    }
    vector <bool> done(n + p + q + 1);
    vector <tuple <int, int, int>> ops;
    for (int i = 1; i <= n; i++){
        if (!done[i]){
            if (!done[i + p]){
                ops.emplace_back(i, i + p, i + p + q);
                done[i] = true;
                done[i + p] = true;
                done[i + p + q] = true;
            }
            else if (!done[i + q]){
                ops.emplace_back(i, i + q, i + p + q);
                done[i] = true;
                done[i + q] = true;
                done[i + p + q] = true;
            }
        }
    }
    cout << ops.size() << "\n";
    for (auto[x, y, z] : ops){
        cout << x << " " << y << " "  << z << "\n";
    }

    return 0;
}   
