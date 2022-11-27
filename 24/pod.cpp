#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int b, q;
	cin >> b >> q;
	vector <lli> freq(b);
	lli digit_sum = 0;
	for (int i = 0; i < b; i++){
		cin >> freq[i];
		digit_sum += freq[i] * i;
	}
	if (digit_sum % (b - 1) != 0){
		freq[digit_sum % (b - 1)]--;
	}
	vector <lli> pref(b);
	pref[0] = freq[0] - 1;
	for (int i = 1; i < b; i++){
		pref[i] = pref[i - 1] + freq[i];
	}

	lli k;
	while (q--){
		cin >> k;
		int ans = lower_bound(pref.begin(), pref.end(), k) - pref.begin();
		cout << (ans < b ? ans : -1) << "\n";
	}

	return 0;
}
