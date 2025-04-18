#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

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
		
		if (l <= s && e <= r){
			return st[i];
		}
		if (l > e || s > r){
			return T::neutral;
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

	void update(int l, int r, int val){
		update(1, 1, n, l, r, val);
	}
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	int n, capacity, q, p, k, l;
	cin >> n >> capacity >> q;
	SegTree <Max> st;
	st.init(n);
	for (int i = 0; i < q; i++){
		cin >> p >> k >> l;
		if (st.query(p, k - 1).val + l > capacity){
			cout << "N\n";
		}
		else{
			st.update(p, k - 1, l);
			cout << "T\n";
		}
	}
	
    return 0;
}
