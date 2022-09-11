//XXII OI
#include <bits/stdc++.h>
#include "ckollib.h"
typedef long long int lli;
using namespace std;

int cnt_bit[31];

void dolicz_bity(int x){
	for (int i = 0; i <= 30; i++){
		if (x & (1 << i)){
			cnt_bit[i]++;
		}
	}
}

void solve(){
	int cnt1 = 0, v1 = karta(), v2 = v1;
	dolicz_bity(v1);
	while (v2 == v1){
		cnt1++;
		v2 = karta();
		dolicz_bity(v2);
	}
	if (v2 == 0){
		odpowiedz(v1);
	}
	int cnt2 = 1, nxt = 1;
	while (nxt != 0){
		nxt = karta();
		dolicz_bity(nxt);
		if (nxt == v1) cnt1++;
		else if (nxt == v2) cnt2++;
	}
	if (cnt1 < cnt2){
		odpowiedz(v1);
		return;
	}
	if (cnt1 > cnt2){
		odpowiedz(v2);
		return;
	}
	
	int ans = 0;
	for (int i = 0; i <= 30; i++){
		cnt_bit[i] %= cnt1;
		if (cnt_bit[i] != 0){
			ans += (1 << i);
		}
	}
	odpowiedz(ans);
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
