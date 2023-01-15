#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int DELTA = 3e4 + 3;

struct P{
    int x, y, type;

    P(int x_ = 0, int y_ = 0, int type_ = 0) : x(x_), y(y_), type(type_) {};

    bool operator < (P &b){
        if (x == b.x){
            if (y == b.y){
                return type > b.type;
            }
            return y < b.y;
        }
        return x < b.x;
    }
};

struct Max{
    static const int neutral = 0;
    int val;

    Max(int val_ = 0) : val(val_) {};

    Max op(Max other){
        return Max(max(val, other.val));
    }
    Max lazy_op(Max v){
        return Max(val + v.val);
    }
};

template <typename T>
struct SegTree{
    int n;
    vector <T> st, lazy;

    void init(int n_){
        n = n_;
        int base = 1;
        while (base <= n){
            base *= 2;
        }
        st.resize(2 * base + 3);
        lazy.resize(2 * base + 3);
    }

    void propagate(int i, int s, int e, T val){
        st[i] = st[i].lazy_op(val);
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

        if (r < s || e < l){
            return T::neutral;
        }
        if (s >= l && e <= r){
            return st[i];
        }

        int mid = (s + e) / 2;
        return query(2 * i, s, mid, l, r).op(query(2 * i + 1, mid + 1, e, l, r));
    }

    T query(int l, int r){
        return query(1, 1, n, l, r);
    }

    void update(int i, int s, int e, int l, int r, int val){
        if (lazy[i].val != 0){
            propagate(i, s, e, lazy[i]);
            lazy[i].val = 0;
        }

        if (r < s || e < l){
            return;
        }
        if (s >= l && e <= r){
            propagate(i, s, e, val);
            return;
        }

        int mid = (s + e) / 2;
        update(2 * i, s, mid, l, r, val);
        update(2 * i + 1, mid + 1, e, l, r, val);
        st[i] = st[2 * i].op(st[2 * i + 1]);
    }

    void update(int l, int r, int val){
        update(1, 1, n, l, r, val);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int w, h, n, x, y, ans = 0;
    cin >> w >> h >> n;
    vector <P> a(2 * n);
    for (int i = 0; i < n; i++){
        cin >> x >> y;
        x += DELTA, y += DELTA;
        a[i] = P(x, y, 1);
        a[i + n] = P(x + w, y + h, -1);
    }
    sort(a.begin(), a.end());

    SegTree <Max> st;
    st.init(2 * DELTA);
    for (auto [x, y, type] : a){
        if (type == 1){
            st.update(y, y + h, 1);
        }
        else{
            st.update(y - h, y, -1);
        }
        ans = max(ans, st.query(1, 2 * DELTA).val);
    }
    cout << ans << "\n";

    return 0;
}   
