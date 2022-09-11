//IV OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define amount first
#define price second

void solve(){
	int cap, n;
	cin >> cap >> n;
	vector <int> p(n), d(n);
	for (int i = 0; i < n; i++){
		cin >> p[i] >> d[i];
	}
	
	int ans = 0, cur_fuel = 0, to_drive, delta;
	deque <pair <int, int>> tank; //pary {amount, price}, back = droga, front = tania
	for (int i = 0; i < n; i++){
		while (!tank.empty() && tank.back().price >= p[i]){
			ans -= tank.back().amount * tank.back().price;
			cur_fuel -= tank.back().amount;
			tank.pop_back();
		}
		ans += (cap - cur_fuel) * p[i];
		tank.emplace_back(cap - cur_fuel, p[i]);
		cur_fuel = cap;
		
		to_drive = d[i];
		while (to_drive > 0){
			delta = min(to_drive, tank.front().amount);
			tank.front().amount -= delta;
			if (tank.front().amount == 0){
				tank.pop_front();
			}
			to_drive -= delta;
		}
		cur_fuel -= d[i];
	}
	while (!tank.empty()){
		ans -= tank.back().amount * tank.back().price;
		tank.pop_back();
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
