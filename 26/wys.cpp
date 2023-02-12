#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

struct Max{
    lli val;
    static const lli NEUTRAL = -(9e18 + 3);

    Max(lli val_ = 0) : val(val_) {};

    Max op(Max other){
        return Max(max(val, other.val));
    }
    Max lazy_op(Max v, int sz){
        return Max(val + v.val);
    }
};

template <typename T>
struct SegTree{
    int n, base;
    vector <T> st, lazy;

    void init(int n_, vector <lli> a, lli d){
        n = n_;
        base = 1;
        while (base <= n){
            base *= 2;
        }
        st.resize(2 * base + 3);
        lazy.resize(2 * base + 3);
        build(1, 1, n, a, d);
    }

    void build(int i, int s, int e, const vector <lli> &a, lli d){
        if (s == e){
            st[i] = a[s] + d * (n + 1 - s); // (n + 1 - s) = points this guy will get after a race
            return;
        }
        int mid = (s + e) / 2;
        build(2 * i, s, mid, a, d);
        build(2 * i + 1, mid + 1, e, a, d);
        st[i] = st[2 * i].op(st[2 * i + 1]);
    }

    void propagate(int i, int s, int e, T val){
        st[i] = st[i].lazy_op(val, e - s + 1);
        if (s != e){
            lazy[2 * i].val += val.val;
            lazy[2 * i + 1].val += val.val;
        }
    }

    T query(int i, int s, int e, int l, int r){
        if (lazy[i].val != 0){
            propagate(i, s, e, lazy[i]);
            lazy[i].val = 0;
        }

        if (l <= s && e <= r){
            return st[i];
        }
        if (l > e || s > r){
            return T::NEUTRAL;
        }

        int mid = (s + e) / 2;
        return query(2 * i, s, mid, l, r).op(query(2 * i + 1, mid + 1, e, l, r));
    }

    T query(int l, int r){
        return query(1, 1, n, l, r);
    }

    void update(int i, int s, int e, int l, int r, lli val){
        if (lazy[i].val != 0){
            propagate(i, s, e, lazy[i]);
            lazy[i].val = 0;
        }

        if (l <= s && e <= r){
            propagate(i, s, e, val);
            return;
        }
        if (l > e || s > r){
            return;
        }

        int mid = (s + e) / 2;
        update(2 * i, s, mid, l, r, val);
        update(2 * i + 1, mid + 1, e, l, r, val);
        st[i] = st[2 * i].op(st[2 * i + 1]);
    }

    void update(int l, int r, lli val){
        update(1, 1, n, l, r, val);
    }

    int lower_bound(lli val){
        int i = 1, s = 1, e = n;
        if (lazy[i].val != 0){
            propagate(i, s, e, lazy[i]);
            lazy[i].val = 0;
        }
        while (s < e){
            int mid = (s + e) / 2;
            bool nothing_geq = true;
            if (lazy[2 * i].val != 0){
                propagate(2 * i, s, mid, lazy[2 * i]);
                lazy[2 * i].val = 0;
            }
            if (st[2 * i].val >= val){
                i *= 2;
                e = mid;
                nothing_geq = false;
            }
            else{
                if (lazy[2 * i + 1].val != 0){
                    propagate(2 * i + 1, mid + 1, e, lazy[2 * i + 1]);
                    lazy[2 * i + 1].val = 0;
                }
                if (st[2 * i + 1].val >= val){
                    i *= 2;
                    i++;
                    s = mid + 1;
                    nothing_geq = false;
                }
            }
            if (nothing_geq) return n + 1;
        }
        return s;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q, i;
    cin >> n >> q;
    vector <lli> a(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    SegTree <Max> st1, st2; 
    st1.init(n, a, 0); 
    st2.init(n, a, 1);

    char t;
    lli x, val;
    while (q--){
        cin >> t;
        if (t == 'Z'){
            i = st1.lower_bound(st2.query(1, n).val - n);
            cout << n - i + 1 << "\n";
        }
        else if (t == 'B'){
            cin >> x >> val;
            i = st1.lower_bound(x);
            if (i <= n){
                st1.update(i, n, val);
                st2.update(i, n, val);
            }
        }
        else{
            cin >> x >> val;
            i = st1.lower_bound(x + 1);
            if (i >= 2){
                st1.update(1, i - 1, -val);
                st2.update(1, i - 1, -val);
            }
        }
    }

    return 0;
}
