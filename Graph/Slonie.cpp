//XVI OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const lli INF = 1e17;

void solve(){
	int n, x;
	lli min_global_mass = INF;
	cin >> n;
	vector <lli> mass(n + 1);
	vector <int> p(n + 1), nxt(n + 1);
	vector <bool> vis(n + 1);
	for (int i = 1; i <= n; i++){
		cin >> mass[i];
		min_global_mass = min(min_global_mass, mass[i]);
	}
	for (int i = 1; i <= n; i++){
		cin >> p[i];
	}
	for (int i = 1; i <= n; i++){
		cin >> x;
		nxt[p[i]] = x;
	}
	lli ans = 0, no_borrow, borrow, min_local_mass, min_local;
	int cur;
	for (int i = 1; i <= n; i++){
		if (!vis[i]){
			min_local_mass = mass[i];
			min_local = i;
			cur = nxt[i];
			while (cur != i){
				if (mass[cur] < min_local_mass){
					min_local_mass = mass[cur];
					min_local = cur;
				}
				cur = nxt[cur];
			}
			no_borrow = 0;
			borrow = (min_local_mass == min_global_mass ? 0 : 2 * (min_local_mass + min_global_mass));
			cur = min_local;
			vis[cur] = true;
			while (!vis[nxt[cur]]){
				no_borrow += min_local_mass + mass[nxt[cur]];
				borrow += min_global_mass + mass[nxt[cur]];
				vis[nxt[cur]] = true;
				cur = nxt[cur];
			}
			ans += min(no_borrow, borrow);
		}
	}
	cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    //cin >> t;
    while (t--){
        solve();
    }
    return 0;
}   
