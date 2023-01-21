#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

struct Sum{
	static const lli NEUTRAL = 0;
	lli val;
 
	Sum(lli val_ = 0) : val(val_) {};
 
	Sum op(Sum other){
		return Sum(val + other.val);
	}
	Sum lazy_op(pair <Sum, Sum> v, lli sz){
		return Sum(val + sz * v.ff.val + v.ss.val * (sz - 1) * sz / 2);
	}
};
 
template <typename T>
struct SegTree{
	lli n;
	vector <T> st;
	vector <pair <T, T>> lazy; // {starting value, difference}
 
	void init(lli n_){
		n = n_;
		lli base = 1;
		while (base <= n){
			base *= 2;
		}
		st.resize(2 * base + 3);
		lazy.resize(2 * base + 3);
	}
 
	void propagate(lli i, lli s, lli e, pair <T, T> val){
		st[i] = st[i].lazy_op(val, e - s + 1);
		if (s != e){
			lazy[2 * i].ff.val += val.ff.val;
			lazy[2 * i].ss.val += val.ss.val;
			lazy[2 * i + 1].ff.val += val.ff.val + ((s + e) / 2 + 1 - s) * val.ss.val;
			lazy[2 * i + 1].ss.val += val.ss.val;
		}
	}
 
	T query(lli i, lli s, lli e, lli l, lli r){
		if (lazy[i].ff.val != 0 || lazy[i].ss.val != 0){
			propagate(i, s, e, lazy[i]);
			lazy[i].ff.val = 0;
			lazy[i].ss.val = 0;
		}
 
		if (l <= s && e <= r){
			return st[i];
		}
		if (l > e || r < s){
			return T::NEUTRAL;
		}
 
		lli mid = (s + e) / 2;
		return query(2 * i, s, mid, l, r).op(query(2 * i + 1, mid + 1, e, l, r));
	}
	
	T query(lli l, lli r){
		return query(1, 1, n, l, r);
	}
 
	void update(lli i, lli s, lli e, lli l, lli r, lli a, lli d){
		if (lazy[i].ff.val != 0 || lazy[i].ss.val != 0){
			propagate(i, s, e, lazy[i]);
			lazy[i].ff.val = 0;
			lazy[i].ss.val = 0;
		}
 
		if (l <= s && e <= r){
			propagate(i, s, e, pair{a + (s - l) * d, d});
			return;
		}
		if (l > e || r < s){
			return;
		}
 
		lli mid = (s + e) / 2;
		update(2 * i, s, mid, l, r, a, d);
		update(2 * i + 1, mid + 1, e, l, r, a, d); 
		st[i] = st[2 * i].op(st[2 * i + 1]);
	}
 
	void update(lli l, lli r, lli a, lli d){
		update(1, 1, n, l, r, a, d);
	}
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    lli n, q, x, l, r, a, d;
    cin >> n >> q;
    SegTree <Sum> st;
    st.init(n);
    vector <pair <lli, lli>> tower(n + 1);

    char type;
    while (q--){
        cin >> type;
        if (type == 'P'){
            cin >> x >> a >> d;
            tower[x] = {a, d};
            l = max(1LL, x - (a + d - 1) / d + 1);
            r = min(n, x + (a + d - 1) / d - 1);
            st.update(l, x, a - (x - l) * d, d);
            if (r > x) st.update(x + 1, r, a - d, -d);
        }
        else if (type == 'U'){
            cin >> x;
            auto[a, d] = tower[x];
            l = max(1LL, x - (a + d - 1) / d + 1);
            r = min(n, x + (a + d - 1) / d - 1);
            st.update(l, x, -(a - (x - l) * d), -d);
            if (r > x) st.update(x + 1, r, -(a - d), d);
            tower[x] = {0, 0};
        }
        else{
            cin >> l >> r;
            cout << st.query(l, r).val / (r - l + 1) << "\n";
        }
    }

    return 0;
}
