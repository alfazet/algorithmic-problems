//VIII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int P = 19;

// nie mozna uzyc P w tych rozkladach
vector <lli> intervals = {P + 10 - 1}, last_prime_in_interval = {0};
vector <int> precomp[P] = {{3, 7}, {11}, {5, 7}, {13}, {3, 11}, {3, 5, 7}, {3, 13}, {17}, {7, 11}, {3, 5, 11}, {7, 13}, {3, 7, 11}, {5, 17}, 
{3, 7, 13}, {7, 17}, {3, 5, 17}, {3, 5, 7, 11}, {3, 11, 13}, {11, 17}};

bool prime(lli n){
	for (lli i = 2; i * i <= n; i++){
		if (n % i == 0){
			return false;
		}
	}
	return true;
}

void fill_intervals(){
	lli all_size = P, p = all_size;
	while (intervals.back() <= 2e9){
		while (!prime(p)){
			p--;
		}
		intervals.push_back(intervals.back() + p);
		last_prime_in_interval.push_back(p);
		all_size = intervals.back() - 10 + 1;
		p = all_size;
	}
}

vector <int> decompose(int n){
	vector <int> ans;
	int i = intervals.size() - 1;
	while (n > P + 10 - 1){
		while (intervals[i] > n){
			i--;
		}
		i++;
		n -= last_prime_in_interval[i];
		ans.push_back(last_prime_in_interval[i]);
	}
	ans.insert(ans.end(), precomp[n - 10].begin(), precomp[n - 10].end());
	return ans;
}

void solve(){
	fill_intervals();
	int q, n;
	cin >> q;
	while (q--){
		cin >> n;
		vector <int> ans = decompose(n);
		sort(ans.begin(), ans.end());
		cout << ans.size() << "\n";
		for (int x : ans){
			cout << x << " ";
		}
		cout << "\n";
	}
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
