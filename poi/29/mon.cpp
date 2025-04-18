#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;
	vector <bool> take(n);
	vector <pair <pair <int, int>, int>> a(n);
	
	for (int i = 0; i < n; i++){
		cin >> a[i].ff.ss >> a[i].ff.ff;
		a[i].ss = i + 1;
	}
	sort(a.begin(), a.end());

	int ans = 0;
	lli t = 0;
	pair <int, int> temp;
	priority_queue <pair <int, int>> pq; 

	for (int i = 0; i < n; i++){
		if (a[i].ff.ff < a[i].ff.ss){
			continue;
		}
		if (t + a[i].ff.ss <= a[i].ff.ff){
			ans++;
			t += a[i].ff.ss;
			pq.push({a[i].ff.ss, i});
			take[i] = true;
		}
		else if (!pq.empty() && pq.top().first > a[i].ff.ss){
			temp = pq.top();
			take[temp.second] = false;
			pq.pop();
			t -= (temp.first - a[i].ff.ss);
			pq.push({a[i].ff.ss, i});
			take[i] = true;
		}
	}

	cout << ans << "\n";
	t = 1;
	for (int i = 0; i < n; i++){
		if (take[i]){
			cout << a[i].ss << " " << t << "\n";
			t += a[i].ff.ss;
		}
	}

	return 0;
}
