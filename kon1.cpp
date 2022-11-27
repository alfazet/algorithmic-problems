//XX OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const int MAXN = 3e5 + 3, INF = 1e9 + MAXN;

int a[MAXN], n, k;

struct Seg_tree{
    int base;
    vector <pair <int, int>> st;
    vector <int> lazy;

    pair <int, int> op(pair <int, int> a, pair <int, int> b){ //{val, id}
        if (a.ff >= b.ff){
            return a;
        }
        else{
            return b;
        }
    }
    
    pair <int, int> neutral(){ //0 for sum, xor, gcd, -INF for max, INF for min
        return {-INF, -1};
    }

    void build(int si, int ss, int se){
        if (ss == se){
            st[si] = {a[ss], ss};
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
        build(1, 0, n - 1);
    }

    void propagate(int si, int ss, int se, int val){ //for other queries / += for add updates, = for set updates
        st[si].ff += val;
        if (ss != se){
            lazy[2 * si] += val;
            lazy[2 * si + 1] += val;
        }
    }

    pair <int, int> query(int si, int ss, int se, int qs, int qe){ 
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

struct Seg_tree2{
    int base;
    vector <int> st;

    int op(int a, int b){ //max, min, sum, xor, gcd...
        return a + b;
    }

    int neutral(){ //0 for sum, xor, gcd, -INF for max, INF for min
        return 0;
    }

    void init(int n){
        base = 1;
        while (base < n){
            base *= 2;
        }
        st.assign(2 * base, neutral());
    }

    int query(int qs, int qe){
        int si_l = base + qs, si_r = base + qe, res = st[si_l];
        if (si_l != si_r){
            res = op(res, st[si_r]);
        }
        while (si_l / 2 != si_r / 2){
            if (si_l % 2 == 0){
                res = op(res, st[si_l + 1]);
            }
            si_l /= 2;
            if (si_r % 2 == 1){
                res = op(res, st[si_r - 1]);
            }
            si_r /= 2;
        }
        return res;
    }

    void update(int ui, int val){
        int si = base + ui;
        //cout << "base, ui: " << base << ", " << ui << "\n";
        st[si] += val;
        while (si > 1){
            si /= 2;
            st[si] = op(st[2 * si], st[2 * si + 1]);
        }
    }
};

Seg_tree st1;
Seg_tree2 st2;

void inicjuj(int n_, int k_, int *a_){
    n = n_;
    k = k_;
    for (int i = 0; i < n; i++){
        a[i] = a_[i];
    }
    st1.init(n);
    st2.init(n);
    for (int i = 0; i < n; i++){
        if (a[i] >= k){
            st1.update(1, 0, n - 1, i, i, -INF);
            st2.update(i, 1);
        }
    }
}

void podlej(int l, int r){
    st1.update(1, 0, n - 1, l, r, 1);
    pair <int, int> mx = st1.query(1, 0, n - 1, l, r);
    while (mx.ff >= k){
        //cout << "najwyzsze w przedziale " << l << ", " << r << ": " << mx.ff << " na pozycji " << mx.ss << "\n";
        st1.update(1, 0, n - 1, mx.ss, mx.ss, -INF);
        st2.update(mx.ss, 1);
        mx = st1.query(1, 0, n - 1, l, r);
    }
}

int dojrzale(int l, int r){
    return st2.query(l, r);
}
