//VI OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

struct Node{
	int min_z, max_z, min_nz, max_nz;
};

void solve(){
	string spec;
	cin >> spec;
	reverse(spec.begin(), spec.end());
	stack <Node> s;
	Node u, w;
	for (char c : spec){
		if (c == '0'){
			s.push({1, 1, 0, 0});
		}
		else if (c == '1'){
			u = s.top();
			s.pop();
			s.push({u.min_nz + 1, u.max_nz + 1, min(u.min_z, u.min_nz), max(u.max_z, u.max_nz)});
		}
		else{
			u = s.top();
			s.pop();
			w = s.top();
			s.pop();
			s.push({u.min_nz + w.min_nz + 1, u.max_nz + w.max_nz + 1, min(u.min_z + w.min_nz, u.min_nz + w.min_z), max(u.max_z + w.max_nz, u.max_nz + w.max_z)});
		}
	}
	Node root = s.top();
	cout << max(root.max_z, root.max_nz) << " " << min(root.min_z, root.min_nz) << "\n";
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
