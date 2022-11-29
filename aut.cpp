#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

struct Stop{
	int x, y, p;
	
	bool operator < (const Stop &s) const{
		if (x == s.x){
			return y < s.y;
		}
		return x < s.x;
	}
	
	void read(){
		cin >> x >> y >> p;
	}
};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m, k;
	cin >> n >> m >> k;
	vector <Stop> a(k);
	for (int i = 0; i < k; i++){
		a[i].read();
	}
	sort(a.begin(), a.end()); // sorted by x, then y
	
	lli here;
	map <int, lli> max_at; // max_at[y] = max. number of people we can collect up to y
	max_at[0] = 0;
	for (int i = 0; i < k; i++){
		auto[x, y, p] = a[i];
		auto it = max_at.upper_bound(y);
		it--; // first non-greater
		here = p + it->ss;
		it++;
		while (it != max_at.end() && it->ss < here){ // removing every pair where we are higher, but with less people
			max_at.erase(it++);
		}
		max_at[y] = max(max_at[y], here);
	}
	cout << max_at.rbegin()->ss << "\n";

	return 0;
}
