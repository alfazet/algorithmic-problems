//IX OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const int INF = 1e9;

void solve(){
	int n, x, ans = 0;
	cin >> n;
	vector <int> h(n), prev_less(n), next_less(n);
	vector <pair <int, int>> st; //  {min, id}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cin >> x;
			if (x == 0) h[j]++;
			else h[j] = 0;	
		}
		// max. rectangle in histogram
		for (int j = 0; j < n; j++){
			while (!st.empty() && st.back().ff >= h[j]){
				st.pop_back();
			}
			if (st.empty()){
				prev_less[j] = j;
			}
			else{
				prev_less[j] = st.back().ss + 1;
			}
			st.push_back({h[j], j});
		}
		st.clear();
		for (int j = n - 1; j >= 0; j--){
			while (!st.empty() && st.back().ff >= h[j]){
				st.pop_back();
			}
			if (st.empty()){
				next_less[j] = j;
			}
			else{
				next_less[j] = st.back().ss - 1;
			}
			st.push_back({h[j], j});
		}
		for (int j = 0; j < n; j++){
			ans = max(ans, h[j] * (next_less[j] - prev_less[j] + 1));
		}
		st.clear();
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
