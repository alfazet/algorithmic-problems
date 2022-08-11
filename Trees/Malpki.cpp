#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;
 
#define ff first
#define ss second
 
const int MAXN = 2e5 + 3, MAXM = 4e5 + 3;

pair <int, int> hold[MAXN], hold_cp[MAXN], timeline[MAXM];
vector <int> members[MAXN];
int par[MAXN], ans[MAXN];

void init_DSU(int n){
	for (int i = 1; i <= n; i++){
		par[i] = i;
		members[i] = {i};
	}
}

void join(int a, int b, const int &t){
	a = par[a];
	b = par[b];
	if (a != b){
		if (members[a].size() < members[b].size()){
			swap(a, b);
		}
		if (a == par[1]){
			for (int m : members[b]){
				ans[m] = t;
			}
		}
		if (b == par[1]){
			for (int m : members[a]){
				ans[m] = t;
			}
		}
		int v;
		while (!members[b].empty()){
			v = members[b].back();
			members[b].pop_back();
			members[a].push_back(v);
			par[v] = a;
		}
	}
}
 
void solve(){
	int n, m, l, r, x, paw;
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		cin >> l >> r;
		hold[i] = hold_cp[i] = {l, r};
	}
	for (int i = 0; i < m; i++){
		cin >> x >> paw;
		if (paw == 1){
			hold[x].ff = -1;
		}
		else{
			hold[x].ss = -1;
		}
		timeline[i] = {x, paw};
	}
	init_DSU(n);
	ans[1] = -1;
	for (int i = 1; i <= n; i++){
		if (hold[i].ff != -1){
			join(i, hold[i].ff, -1);
		}
		if (hold[i].ss != -1){
			join(i, hold[i].ss, -1);
		}
	}
	for (int i = m - 1; i >= 0; i--){
		if (timeline[i].ss == 1){
			join(timeline[i].ff, hold_cp[timeline[i].ff].ff, i);
		}
		else{
			join(timeline[i].ff, hold_cp[timeline[i].ff].ss, i);
		}
	}
	for (int i = 1; i <= n; i++){
		cout << ans[i] << "\n";
	}
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
