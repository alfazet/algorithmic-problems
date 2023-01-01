#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

struct P{
    int x, y, id, type;

    P(int x_ = 0, int y_ = 0, int id_ = 0, int type_ = 0) : x(x_), y(y_), id(id_), type(type_) {};
};

struct CompSweep{
    bool operator() (const P &A, const P &B) const{
        if (A.y == B.y){
            return A.x > B.x;
        }
        return A.y < B.y;
    }
};

struct CompSort{ // opposite of the sweep line comparator so that we can use lower_bound
    bool operator() (const P &A, const P &B) const{
        if (A.x == B.x){
            return A.y > B.y;
        }
        return A.x < B.x;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int n;
    cin >> n;
    vector <P> a(2 * n);
    for (int i = 0; i < n; i++){
        cin >> a[i].x >> a[i].y;
        a[i].id = i + 1;
        a[i].type = 0;
    }
    for (int i = 0; i < n; i++){
        cin >> a[i + n].x >> a[i + n].y;
        a[i + n].id = i + 1;
        a[i + n].type = 1;
    }
    sort(a.begin(), a.end(), CompSort());

    lli ans = 0;
    vector <int> match(n + 1);
    set <P, CompSweep> sweep;
    for (P p : a){
        if (p.type == 0){
            sweep.insert(p);
        }
        else{
            auto it = sweep.lower_bound(p);
            P x = *it;
            sweep.erase(it);
            ans += p.x - x.x + x.y - p.y;
            match[x.id] = p.id;
        }
    }

    cout << ans << "\n";
    for (int i = 1; i <= n; i++){
        cout << i << " " << match[i] << "\n"; 
    }

    return 0;
}
