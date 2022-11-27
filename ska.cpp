//XII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int maxn = 1e6 + 3;

int par[maxn], sz[maxn];

int find(int x){
    if (par[x] == x){
        return x;
    }
    return par[x] = find(par[x]);
}

bool merge(int a, int b){
    a = find(a);
    b = find(b);
    if (a == b){
        return false;
    }
    if (sz[a] < sz[b]){
        swap(a, b);
    }
    par[b] = a;
    sz[a] += sz[b]; 
    return true;
}

void solve(){
    int n, x;
    cin >> n;
    for (int i = 1; i <= n; i++){
        par[i] = i;
        sz[i] = 1;
    }
    int cc = n;
    for (int i = 1; i <= n; i++){
        cin >> x;
        if (merge(i, x)){
            cc--;
        }
    }
    cout << cc << "\n";
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
