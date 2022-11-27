//XVIII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

bool isTriangle(int a, int b, int c){
    return (a + b > c && a + c > b && b + c > a);
}

bool diffColors(int a, int b, int c){
    return (a != b && b != c && a != c);
}

int findNext(const vector <pair <int, int>> &a, int n, int i){
    int col = a[i].second;
    while (i + 1 < n && a[i + 1].second == col){
        i++;
    }
    return i;
}

void solve(){
    int k, n, x;
    vector <pair <int, int>> sticks;
    cin >> k;
    for (int i = 1; i <= k; i++){
        cin >> n;
        for (int j = 0; j < n; j++){
            cin >> x;
            sticks.push_back({x, i});
        }
    }
    sort(sticks.begin(), sticks.end());
    int sz = sticks.size();
    sticks.push_back({-1, -1});

    int p = 0, i, j, a, b, c, ca, cb, cc;
    while (true){
        i = findNext(sticks, sz, p);
        j = findNext(sticks, sz, i + 1);
        k = j + 1;
        p = j;
        if (i < sz && j < sz && k < sz){
            a = sticks[i].first;
            ca = sticks[i].second;
            b = sticks[j].first;
            cb = sticks[j].second;
            c = sticks[k].first;
            cc = sticks[k].second;
            if (isTriangle(a, b, c) && diffColors(ca, cb, cc)){
                cout << ca << " " << a << " " << cb << " " << b << " " << cc << " " << c << "\n";
                return;
            }
        }
        else{
            break;
        }
    }
    cout << "NIE\n";
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
