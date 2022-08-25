#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 603;
const lli INF = 1e18 + 3;

struct P{
    lli x, y;
    void read(){
        cin >> x >> y;
    }
    void print(){
        cout << "(" << x << ", " << y << ")\n";
    }
    bool operator <(const P &a){ //
        return x < a.x || (x == a.x && y < a.y);
    }
    bool operator ==(const P &a){
        return x == a.x && y == a.y;
    }
    P operator -(const P& b) const{
        return P{x - b.x, y - b.y};
    }
    lli operator *(const P& b) const{
        return x * b.y - y * b.x;
    }

    //returns x, |x| = 2 * area of triangle, x > 0 <==> when going A->B->C we turn ccwise (+ve angle)
    lli orient(const P& b, const P& c) const { 
        return (b - *this) * (c - *this);
    }
};

P poly[MAXN];
lli halfplane[MAXN][MAXN];

void solve(){
    int n, m, x, y, zysk, l, r, mid;
    lli total = 0;
    P fab;
    cin >> n;
    for (int i = 0; i < n; i++){
        poly[i].read();
    }
    cin >> m;
    for (int i = 0; i < m; i++){
        fab.read();
        cin >> zysk;
        total += zysk;
        for (int j = 0; j < n; j++){
            if (fab == poly[j]){
                continue;
            }
            l = j + 1, r = j + n - 1;
            while (l < r){
                mid = (l + r) / 2;
                if (poly[j].orient(poly[mid % n], fab) <= 0){
                    l = mid + 1;
                }
                else{
                    r = mid;
                }
            }
            if (poly[j].orient(poly[l % n], fab) != 0){
                halfplane[j][l % n] += zysk;
            }
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 2; j < n; j++){
            halfplane[i][(i + j) % n] += halfplane[i][(i + j - 1) % n];
        }
    }
    lli best = -INF;
    for (int i = 0; i < n - 2; i++){
        for (int j = i + 1; j < n - 1; j++){
            for (int k = j + 1; k < n; k++){
                best = max(best, total - halfplane[i][j] - halfplane[j][k] - halfplane[k][i]);
            }
        }
    }
    cout << best << "\n";
}

int main(){
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
