#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	int n, H, ans = 0, dh = 0;
	char c;
	cin >> n >> H;
  	vector <int> h(n + 1);
	for (int i = 1; i <= n; i++){
		h[i] = h[i - 1];
		cin >> c;
		if (c == '(') h[i]++;
		else h[i]--;
	}
	for (int i = 0; i < n; i++){
		h[i] += dh;
		if (h[i] > H){
			int open = (h[i] - H) / 2 + ((h[i] - H) % 2);
			ans += open;
			dh -= 2 * open;
		}
		if (h[i] < 0){
			ans++;
			dh += 2;
		}
	}
	cout << ans << "\n";
	
    return 0;
}
