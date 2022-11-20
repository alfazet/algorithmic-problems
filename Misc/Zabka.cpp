#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	int n, k;
	lli jumps;
	cin >> n >> k >> jumps;
	vector <int> nxt(n), new_nxt(n), ans(n);
	vector <lli> p(n);
	for (int i = 0; i < n; i++){
		cin >> p[i];
		ans[i] = i;
	}
	nxt[0] = k;
	
	int ptr = 0;
	for (int i = 1; i < n; i++){
		while (ptr + k + 1 < n && p[ptr + k + 1] - p[i] < p[i] - p[ptr]){
			ptr++;
		}
		if (p[i] - p[ptr] >= p[ptr + k] - p[i]){
			nxt[i] = ptr;
		}
		else{
			nxt[i] = ptr + k;
		}
	}
	
	for (int b = 0; b <= 60; b++){
		if ((1LL << b) & jumps){
			for (int i = 0; i < n; i++){
				ans[i] = nxt[ans[i]];
			}
		}
		for (int i = 0; i < n; i++){
			new_nxt[i] = nxt[nxt[i]];
		}
		nxt = new_nxt;
	}
	for (int i = 0; i < n; i++){
		cout << ans[i] + 1 << " ";
	}
	cout << "\n";
	
    return 0;
}   
