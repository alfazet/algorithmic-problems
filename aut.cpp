//XII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;	

struct Stop{
	int x, y, n;
	
	void print(){
		cout << "(" << x << ", " << y << ", " << n << ")\n";
	}
};

bool comp(Stop s1, Stop s2){
	if (s1.x == s2.x){
		return s1.y < s2.y;
	}
	return s1.x < s2.x;
}

void solve(){
	int W, H, k;
	cin >> W >> H >> k;
	vector <Stop> stops(k);
	for (int i = 0; i < k; i++){
		cin >> stops[i].x >> stops[i].y >> stops[i].n;
	}
	sort(stops.begin(), stops.end(), comp);
	map <int, int> mp;
	mp[0] = 0;
	int here;
	for (int i = 0; i < k; i++){
		auto it = mp.upper_bound(stops[i].y);
		it--;
		here = it->second + stops[i].n;
		it++;
		while (it != mp.end() && it->second < here){
			mp.erase(it++);
		}
		mp[stops[i].y] = max(mp[stops[i].y], here);	

	}
	cout << (mp.rbegin())->second << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    // cin >> t;
    while (t--){
        solve();
    }
    return 0;
}   
