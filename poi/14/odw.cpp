#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

bool check(int k, vector <int> &mass, priority_queue <int> pq){
	int taken = 0, mx;
	for (int i = k - 1; i >= 0; i--){
		mx = pq.top();
		pq.pop();
		if (mass[i] <= mx){
			mx -= mass[i];
			taken++;
		}
		else{
			break;
		}
		pq.push(mx);
	}
	return taken >= k;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	int n, m, x;
	cin >> n >> m;
	priority_queue <int> pq;
	vector <int> mass(m);
	for (int i = 0; i < n; i++){
		cin >> x;
		pq.push(x);
	}
	for (int i = 0; i < m; i++){
		cin >> mass[i];
	}
	sort(mass.begin(), mass.end());

	int l = 0, r = m, mid, ans = l;
	while (l <= r){
		mid = (l + r) / 2;
		if (check(mid, mass, pq)){
			ans = max(ans, mid);
			l = mid + 1;
		}
		else{
			r = mid - 1;
		}
	}
	cout << ans << "\n";

    return 0;
}   
