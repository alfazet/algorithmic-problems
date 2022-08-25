#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

struct P{
    int x, y, typ, id; //0 - punkt, 1 - stacja
};

bool operator == (P A, P B){
  return (A.x == B.x && A.y == B.y && A.id == B.id);
}

struct compSweep{
    bool operator() (P A, P B) const{
        if (A.y < B.y){
            return true;
        }
        if (A.y == B.y && A.x > B.x){
            return true;
        }
        return false;
    }
};

struct compVector{
    bool operator() (P A, P B) const{
        if (A.x < B.x){
            return true;
        }
        if (A.x == B.x && A.y > B.y){
            return true;
        }
        return false;
    }
};

void solve(){
    int n;
    cin >> n;
    vector <P> a(2 * n);
    for (int i = 0; i < n; i++){
        cin >> a[i].x >> a[i].y; 
        a[i].id = i + 1;
        a[i].typ = 0;
    }
    for (int i = n; i < 2 * n; i++){
        cin >> a[i].x >> a[i].y; 
        a[i].id = i + 1 - n;
        a[i].typ = 1;
    }
    sort(a.begin(), a.end(), compVector());


    lli ans = 0;
    vector <pair <int, int>> ans_vec;
    set <P, compSweep> sweep;
    set <P, compSweep> :: iterator it;
    P punkt;

    for (int i = 0; i < 2 * n; i++){
        if (a[i].typ == 0){
            sweep.insert(a[i]);
        }
        else{
            it = sweep.lower_bound(a[i]);
            punkt = *it; //znaleziony punkt wydobycia
            ans += (punkt.y - a[i].y) + (a[i].x - punkt.x);
            ans_vec.emplace_back(punkt.id, a[i].id);
            sweep.erase(it);
        }
    }

    cout << ans << "\n";
    for (pair <int, int> p : ans_vec){
        cout << p.first << " " << p.second << "\n";
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
