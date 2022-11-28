#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

lli n, ans = 2e9 + 3;
int max_divs_cnt;

void rec(lli cur, int max_e, int cur_prime_id, int divs_cnt){
	if (divs_cnt > max_divs_cnt || (divs_cnt == max_divs_cnt && cur < ans)){
		max_divs_cnt = divs_cnt;
		ans = cur;
	}
	
	if (cur_prime_id == 10){
		return;
	}
	
	lli power = 1;
	for (int e = 1; e <= max_e; e++){
		power *= primes[cur_prime_id];
		if (cur * power <= n){
			rec(cur * power, e, cur_prime_id + 1, divs_cnt * (e + 1));
		}
		else{
			return;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	rec(1, 32, 0, 1);
	cout << ans << "\n";

	return 0;
}
