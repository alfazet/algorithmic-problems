#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);

	int n, next, gain, gain_if_switch;
	cin >> n;
	vector <int> cake(n + 1), ans(n + 1), shared(n + 1);
	for (int i = 1; i <= n; i++){
		cin >> cake[i];
		cake[i] *= 2;
	}
	for (int i = 1; i <= n; i++){
		next = (i % n) + 1;
		if (cake[i] >= cake[next]){
			ans[i] = i;
			shared[i]++;
		}
		else{
			ans[i] = next;
			shared[next]++;
		}
	}
	for (int i = 1; i <= n; i++){
		next = (i % n) + 1;
		gain = cake[ans[i]];
		if (shared[ans[i]] == 2){
			gain /= 2;
		}
		if (ans[i] == i){
			gain_if_switch = cake[next];
			if (shared[next] == 1){
				gain_if_switch /= 2;
			}
			if (gain_if_switch > gain){
				shared[ans[i]]--;
				ans[i] = next;
				shared[ans[i]]++;
			}
		}
		else{
			gain_if_switch = cake[i];
			if (shared[i] == 1){
				gain_if_switch /= 2;
			}
			if (gain_if_switch > gain){
				shared[ans[i]]--;
				ans[i] = i;
				shared[ans[i]]++;
			}
		}
	}
	for (int i = 1; i <= n; i++){
		cout << ans[i] << " ";
	}
	cout << "\n";
	
	return 0;
}
