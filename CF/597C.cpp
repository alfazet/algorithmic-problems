#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e5 + 3;

template <typename T>
struct BIT{
    int n;
    vector <T> bit;

    void init(int n_, vector <T> a = {}){
        n = n_;
        bit.resize(n + 1);
        if (!a.empty()){
            for (int i = 1; i <= n; i++){
                update(i, a[i]);
            }
        }
    }

    T query(int i){
        T ans = 0;
        while (i >= 1){
            ans += bit[i];
            i -= (i & -i);
        }
        return ans;
    }

    T query(int l, int r){
        return query(r) - (l == 1 ? 0 : query(l - 1));
    }

    void update(int i, T val){
        while (i <= n){
            bit[i] += val;
            i += (i & -i);
        }
    }
};

lli dp[MAXN][13]; // dp[x][i] - number of subsequences that end with x and have length i
BIT <lli> bit[13];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k, x;
	cin >> n >> k;
	
    for (int i = 0; i <= k + 1; i++){
        bit[i].init(n + 1);
    }

	bit[0].update(1, 1);
	for (int i = 0; i < n; i++){
		cin >> x;
        x++; // since we're using a BIT
		for (int j = k + 1; j >= 1; j--){
			dp[x][j] += bit[j - 1].query(1, x - 1);
			bit[j].update(x, dp[x][j]);
		}
	}
	
	lli ans = 0;
	for (int i = 1; i <= n + 1; i++){
		ans += dp[i][k + 1];
	}
	cout << ans << "\n";
	
	return 0;
}
