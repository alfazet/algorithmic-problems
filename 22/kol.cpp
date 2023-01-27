#include <bits/stdc++.h>
#include "ckollib.h"
typedef long long int lli;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	vector <int> freq_bit(32);

	auto add_bits = [&](int x){
		for (int i = 0; i <= 31; i++){
			if ((1 << i) & x){
				freq_bit[i]++;
			}
		}
	};

	int k1 = karta(), k2 = 0, k = 1, f1 = 1, f2 = 0;
	add_bits(k1);
	while (true){
		k = karta();
		if (k == 0){
			break;
		}

		add_bits(k);
		if (k == k1){
			f1++;
		}
		else if (k2 == 0){
			k2 = k;
		}
		if (k == k2){
			f2++;
		}
	}

	if (f2 == 0){
		odpowiedz(k1);
	}
	else if (f1 < f2){
		odpowiedz(k1);
	}
	else if (f2 < f1){
		odpowiedz(k2);
	}
	else{
		int ans = 0;
		for (int i = 0; i <= 31; i++){
			if (freq_bit[i] % f1 != 0){
				ans |= (1 << i);
			}
		}
		odpowiedz(ans);
	}

    return 0;
}   
