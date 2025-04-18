#include <bits/stdc++.h>
#include "maja.h"
typedef long long int lli;
using namespace std;

const int MAXN = 1e6 + 3;

bool is_prime[MAXN];

void sieve(int n){
	for (int i = 2; i <= n; i++){
		is_prime[i] = true;
	}
	is_prime[1] = false;
	for (int i = 2; i * i <= n; i++){
		if (is_prime[i]){
			for (int j = i * i; j <= n; j += i){
				is_prime[j] = false;
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	sieve(1e6);

	while (true){
		int n = gramy_dalej();
		if (n == 0){
			break;
		}
		
		int k = 1, power;
		
		for (int i = 2; i <= n; i++){
			if (is_prime[i]){
				power = i;
				while (power <= n && czy_podzielna_przez(power)){
					k *= i;
					n /= i;
					power *= i;
				}
			}
		}
		zgaduj(k);
	}

	return 0;
}
