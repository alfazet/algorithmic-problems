#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int TRANS = 2e5;

struct Seg_tree{
    const int INF_INT = 1e9 + 3;
    const lli INF_LL = 1e18 + 3;
    int base;
    vector <int> st, lazy;

    int op(int a, int b){ //max, min, sum, xor, gcd...
        return max(a, b);
    }

    int neutral(){ //0 for sum, xor, gcd, -INF for max, INF for min
        return 0;
    }

    void build(int si, int ss, int se){
        if (ss == se){
            //st[si] = a[ss];
            return;
        }
        int mid = (ss + se) / 2;
        build(2 * si, ss, mid);
        build(2 * si + 1, mid + 1, se);
        st[si] = op(st[2 * si], st[2 * si + 1]);
    }

    void init(int n){
        base = 1;
        while (base < n){
            base *= 2;
        }
        st.assign(2 * base, neutral());
        lazy.assign(2 * base, 0);
        //build(1, 0, n - 1);
    }

    void propagate(int si, int ss, int se, int val){ //for other queries / += for add updates, = for set updates
        st[si] += val;
        if (ss != se){
            lazy[2 * si] += val;
            lazy[2 * si + 1] += val;
        }
    }

    int query(int si, int ss, int se, int qs, int qe){ 
        if (lazy[si] != 0){
            propagate(si, ss, se, lazy[si]);
            lazy[si] = 0;
        }

        if (ss > qe || se < qs){
            return neutral();
        }
        if (ss >= qs && se <= qe){
            return st[si];
        }

        int mid = (ss + se) / 2;
        return op(query(2 * si, ss, mid, qs, qe), query(2 * si + 1, mid + 1, se, qs, qe));
    }

    void update(int si, int ss, int se, int us, int ue, int val){ 
        if (lazy[si] != 0){
            propagate(si, ss, se, lazy[si]);
            lazy[si] = 0;
        }

        if (ss > ue || se < us){
            return;
        }
        if (ss >= us && se <= ue){
            propagate(si, ss, se, val);
            return;
        }

        int mid = (ss + se) / 2;
        update(2 * si, ss, mid, us, ue, val);
        update(2 * si + 1, mid + 1, se, us, ue, val);
        st[si] = op(st[2 * si], st[2 * si + 1]);
    }
};

struct Photo{
    int x, y, typ, h;
    bool operator < (Photo p){
        if (x == p.x){
            if (y == p.y){
                return typ > p.typ;
            }
            return y < p.y;
        }
        return x < p.x;
    }
};

void solve(){
    int n, ax, ay, bx, by, ans = 0;
    cin >> n;
    vector <Photo> a(2 * n);
    for (int i = 0; i < n; i++){
        cin >> ax >> ay >> bx >> by;
        a[i] = {ax + TRANS, ay + TRANS, 1, by - ay};
        a[i + n] = {bx + TRANS, by + TRANS, -1, by - ay};
    }
    sort(a.begin(), a.end());
    Seg_tree st;
    st.init(2 * TRANS + 1);
    for (Photo p : a){
        if (p.typ == 1){
            st.update(1, 0, 2 * TRANS, p.y, p.y + p.h, 1);
        }
        else{
            st.update(1, 0, 2 * TRANS, p.y - p.h, p.y, -1);
        }
        ans = max(ans, st.query(1, 0, 2 * TRANS, 0, 2 * TRANS));
    }
    cout << ans << "\n";
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
