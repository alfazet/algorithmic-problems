#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const lli INF = 9e18 + 3;

struct Min{
	static const lli neutral = 9e18 + 3;
	lli val;

	Min() : val(0) {};
	Min(lli val_) : val(val_) {};

	Min op(Min other){
		return Min(min(val, other.val));
	}
	Min lazy_op(Min v, int sz){
		return Min(val + v.val);
	}
};

template <typename T>
struct SegTree{
    int n;
    vector <T> st, lazy;

    void init(int n_, vector <lli> a = {}){
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

    void build(int i, int s, int e, const vector <lli> &a){
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

    void update(int i, int s, int e, int l, int r, lli val){
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

    void update(int l, int r, lli val){
        return update(1, 1, n, l, r, val);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector <int> a(n);
    vector <lli> dp(n + 1);

    for (int i = 1; i < n; i++){
        cin >> a[i];
    }

    vector <lli> b(n + 1, INF);
    b[n] = n;

    SegTree <Min> st;
    st.init(n, b);

    lli ans = 0;
    dp[n] = 0;
    for (int i = n - 1; i >= 1; i--){
        dp[i] = st.query(i + 1, a[i]).val + n - a[i] - i;
        st.update(i, i, dp[i] + i - INF);
        ans += dp[i];
    }
    cout << ans << "\n";

    return 0;
}   
