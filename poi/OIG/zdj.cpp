#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int DELTA = 2e5 + 3;

struct P{
    int x, y, h, type; // 0/1 - photo starts/ends
    
    P(int x_ = 0, int y_ = 0, int h_ = 0, int type_ = 0) : x(x_), y(y_), h(h_), type(type_) {};
    
    bool operator < (const P &B) const{ // sort by x so we can sweep with a vertical line
        if (x == B.x){
            if (y == B.y){
                return type < B.type; 
            }
            return y < B.y;
        }
        return x < B.x;
    }
};

struct Max{
	static const int neutral = -(1e9 + 3);
	int val;

	Max() : val(0) {};
	Max(int val_) : val(val_) {};

	Max op(Max other){
		return Max(max(val, other.val));
	}
	Max lazy_op(Max v, int sz){
		return Max(val + v.val);
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
            st[i] = a[s];
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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x1, y1, x2, y2;
    cin >> n;
    vector <P> a(2 * n);
    for (int i = 0; i < n; i++){
        cin >> x1 >> y1 >> x2 >> y2;
        a[i] = P(x1 + DELTA, y1 + DELTA, y2 - y1, 0);
        a[i + n] = P(x2 + DELTA, y2 + DELTA, y2 - y1, 1); 
    }
    sort(a.begin(), a.end());
    
    int ans = 0;
    SegTree <Max> st;
    st.init(2 * DELTA);
    for (auto [x, y, h, type] : a){
        if (type == 0){
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
