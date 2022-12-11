#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int BASE = (1 << 16);

int n, st[2 * BASE + 3], lazy[2 * BASE + 3];

void propagate(int i, int s, int e, int val){
	st[i] += val;
	if (s != e){
		lazy[2 * i] += val;
		lazy[2 * i + 1] += val;
	}
}

int query(int i, int s, int e, int l, int r){
	if (lazy[i] != 0){
		propagate(i, s, e, lazy[i]);
		lazy[i] = 0;
	}
	
	if (l <= s && e <= r){
		return st[i];
	}
	if (l > e || s > r){
		return 0;
	}
	
	int mid = (s + e) / 2;
	return max(query(2 * i, s, mid, l, r), query(2 * i + 1, mid + 1, e, l, r));
}

int query(int l, int r){
	return query(1, 1, n, l, r);
}

void update(int i, int s, int e, int l, int r, int val){
	if (lazy[i] != 0){
		propagate(i, s, e, lazy[i]);
		lazy[i] = 0;
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
	st[i] = max(st[2 * i], st[2 * i + 1]);
}

void update(int l, int r, int val){
	update(1, 1, n, l, r, val);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	int capacity, q, p, k, l;
	cin >> n >> capacity >> q;
	for (int i = 0; i < q; i++){
		cin >> p >> k >> l;
		if (query(p, k - 1) + l > capacity){
			cout << "N\n";
		}
		else{
			update(p, k - 1, l);
			cout << "T\n";
		}
	}
	
    return 0;
}
