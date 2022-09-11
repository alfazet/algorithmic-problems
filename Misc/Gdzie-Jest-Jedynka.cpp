//XX OI
#include <bits/stdc++.h>
#include "cgdzlib.h"
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const int MAXN = 5e5 + 3;

int perm[MAXN];

pair <int, int> rec(int l, int r, int d){
    if (r - l == 2){
        return {perm[l], perm[l + 1]};
    }
    int mid = l + 1;
    for (int i = l + 1; i < r; i++){
        if (f(perm[l], perm[i], 2 * d) == 1){
            swap(perm[i], perm[mid]);
            mid++;
        }
    }
    if (mid - l == r - mid){
        pair <int, int> p1 = rec(l, mid, 2 * d), p2 = rec(mid, r, 2 * d);
        int mx1 = p1.ff, mx2 = p1.ss, mx3 = p2.ff, mx4 = p2.ss, delta = (r - l - 1) * d;
        if (f(mx1, mx3, delta) == 1){
            return {mx1, mx3};
        }
        else if (f(mx1, mx4, delta) == 1){
            return {mx1, mx4};
        }
        else if (f(mx2, mx3, delta) == 1){
            return {mx2, mx3};
        }
        else{
            return {mx2, mx4};
        }
    }
    else if (mid - l > r - mid){
        return rec(l, mid, 2 * d);
    }
    else{
        return rec(mid, r, 2 * d);
    }
}

void solve(){
	int n = inicjuj();
    if (n == 1){
        odpowiedz(1);
    }
    for (int i = 0; i < n; i++){
        perm[i] = i + 1;
    }
    pair <int, int> p = rec(0, n, 1);
    if (g(p.ff, p.ss) == 0){
        odpowiedz(p.ff);
    }
    odpowiedz(p.ss);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	int t;
	t = 1;
	//cin >> t;
	while (t--){
		solve();
	}
	return 0;
}
