//IV OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int maxn = 1e4 + 5;

pair <int, int> a[maxn];
int dp[maxn];

bool comp(const pair <int, int> &a, const pair <int, int> &b){
	if (a.second < b.second){
		return true;
	}
	return a.first < b.first;
}

int bSearch(int l, int r, int val){
	int mid, ans = 0;
	while (l <= r){
		mid = (l + r) / 2;
		if (a[mid].second <= val){
			ans = mid;
			l = mid + 1;
		}
		else{
			r = mid - 1;
		}
	}
	return dp[ans];
}

void solve(){
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i].first >> a[i].second;
	}
	sort(a + 1, a + n + 1, comp);
	dp[0] = 0;
	for (int i = 1; i <= n; i++){
		dp[i] = max(dp[i - 1], a[i].second - a[i].first + bSearch(0, i, a[i].first));
	}
	cout << dp[n] << "\n";
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
