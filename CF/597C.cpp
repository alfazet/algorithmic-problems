#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e5 + 3;

struct Sum{
	static const lli neutral = 0;
	lli val;

	Sum() : val(0) {};
	Sum(lli val_) : val(val_) {};

	Sum op(Sum other){
		return Sum(val + other.val);
	}
	Sum lazy_op(Sum v, int sz){
		return Sum(val + v.val * sz);
	}
};

template <typename T>
struct SegTree{
	int n;
	vector <T> st, lazy;
	
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
	
	SegTree(int n_ = MAXN, vector <int> a = {}) : n(n_) {
		int base = 1;
		while (base <= n){
			base *= 2;
		}
		st.resize(2 * base + 3);
		lazy.resize(2 * base + 3);
		if (!a.empty()){
			build(1, 0, n, a);
		}
	}; 
	
	void propagate(int i, int s, int e, T val){
		st[i] = st[i].lazy_op(val, e - s + 1);
		if (s != e){
			lazy[2 * i].val += val.val;
			lazy[2 * i + 1].val += val.val;
		}
	}
	
	T query(int i, int s, int e, int l, int r){
		propagate(i, s, e, lazy[i]);
		lazy[i] = 0;
		
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
		return query(1, 0, n, l, r);
	}
	
	void update(int i, int s, int e, int l, int r, T val){
		propagate(i, s, e, lazy[i]);
		lazy[i] = 0;
		
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
	
	void update(int l, int r, T val){
		update(1, 0, n, l, r, val);
	}
};

lli dp[MAXN][12]; // dp[x][i] - number of subsequences that end with x and have length i
SegTree <Sum> st[12];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k, x;
	cin >> n >> k;
	
	st[0].update(0, 0, 1);
	for (int i = 0; i < n; i++){
		cin >> x;
		for (int j = k + 1; j >= 1; j--){
			dp[x][j] += st[j - 1].query(0, x - 1).val;
			st[j].update(x, x, dp[x][j]);
		}
	}
	
	lli ans = 0;
	for (int i = 1; i <= n; i++){
		ans += dp[i][k + 1];
	}
	cout << ans << "\n";
	
	return 0;
}
