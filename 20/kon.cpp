#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const int INF = 1e9 + 3;

struct Max{
    static const lli neutral = -INF;
    int val, i;

    Max() : val(0), i(-1) {};
    Max(int val_) : val(val_), i(-1) {};
    Max(pair <int, int> val_) : val(val_.ff), i(val_.ss) {};

    Max op(Max other){
        return Max(max(pair{val, i}, pair{other.val, other.i}));
    }
    Max lazy_op(Max v, int sz){
        return Max(pair{val + v.val, i});
    }
};

template <typename T>
struct SegTree{
    int n;
    vector <T> st, lazy;

    void init(int n_, vector <int> a = {}){
        n = n_;
        int base = 1;
        while (base <= n){
            base *= 2;
        }
        st.resize(2 * base + 3);
        lazy.resize(2 * base + 3);
        if (!a.empty()){
            build(1, 1, n, a);
        }
    }

    void build(int i, int s, int e, const vector <int> &a){
        if (s == e){
            st[i] = pair{a[s], s};
            return;
        }
        int mid = (s + e) / 2;
        build(2 * i, s, mid, a);
        build(2 * i + 1, mid + 1, e, a);
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

        if (l > e || r < s){
            return T::neutral;
        }
        if (l <= s && e <= r){
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

        if (l > e || r < s){
            return;
        }
        if (l <= s && e <= r){
            propagate(i, s, e, val);
            return;
        }

        int mid = (s + e) / 2;
        update(2 * i, s, mid, l, r, val);
        update(2 * i + 1, mid + 1, e, l, r, val);
        st[i] = st[2 * i].op(st[2 * i + 1]);
    }

    void update(int l, int r, int val){
        return update(1, 1, n, l, r, val);
    }
};

template <typename T>
struct BIT{
    int n;
    vector <T> bit;

    void init(int n_, vector <T> a = {}){
        n = n_;
        bit.resize(n + 1);
        if (!a.empty()){
            for (int i = 1; i <= n; i++){
                update(i, a[i]);
            }
        }
    }

    T query(int i){
        T ans = 0;
        while (i >= 1){
            ans += bit[i];
            i -= (i & -i);
        }
        return ans;
    }

    T query(int l, int r){
        return query(r) - (l == 1 ? 0 : query(l - 1));
    }

    void update(int i, T val){
        while (i <= n){
            bit[i] += val;
            i += (i & -i);
        }
    }
};

SegTree <Max> st;
BIT <int> bit;
int n, limit;

void inicjuj(int n_, int limit_, int *a_){ 
    n = n_;
    limit = limit_;
    vector <int> a(n + 1);
    for (int i = 1; i <= n; i++){
        a[i] = a_[i - 1];
    }
    st.init(n, a);
    bit.init(n);
}

int dojrzale(int l, int r){
    l++, r++;
    while (true){
        auto[mx, i] = st.query(1, n);
        if (mx < limit){
            break;
        }
        st.update(i, i, -INF); // "remove" from segment tree
        bit.update(i, 1); // add to BIT
    }
    return bit.query(l, r);
}

void podlej(int l, int r){
    l++, r++;
    st.update(l, r, 1);
}
